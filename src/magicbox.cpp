# include <Arduino.h>
# include <LiquidCrystal_I2C.h>
# include <LoRa.h>
# include <WiFi.h>
# include <WiFiUdp.h>

// Sylo
# include <sylo/logging.hpp>

# include "magicontent/defines.hpp"
# include "magicontent/mbcp.hpp"
# include "magicontent/music.hpp"
# include "magicontent/magicbox.hpp"

# define LOG_LEVEL LOG_LEVEL_TRACE

namespace magicbox {
    EventGroup events;

    /* Variables */
        uint8_t remotes;

        bool js_sw_pressed = false;
        bool a1_pressed = false;
        bool a2_pressed = false;
        bool a3_pressed = false;
        bool ult_pressed = false;
        bool re_sw_pressed = false;

        int16_t js_x, js_y;
        JoyStickCoord js_coord_x, js_coord_y;
    /**/

    /* Configs */
        const char* UDP_TARGET_IP = nullptr;
        uint16_t UDP_TARGET_PORT = MAGICBOX_DEFAULT_PORT;
    /**/

    /* Objects */
        LiquidCrystal_I2C lcd(0x27, 20, 4);
        RotaryEncoder encoder (MAGICBOX_PIN_RE_SW, MAGICBOX_PIN_RE_DT, MAGICBOX_PIN_RE_CL);
        WiFiUDP udp;
    /**/

    /// Timer components for the MagicBox
    namespace time {
        TOff 
            js_sw_toff (MAGICBOX_BUTTON_TIME), 
            a1_toff (MAGICBOX_BUTTON_TIME),
            a2_toff (MAGICBOX_BUTTON_TIME),
            a3_toff (MAGICBOX_BUTTON_TIME),
            ult_toff (MAGICBOX_BUTTON_TIME),
            re_sw_toff (MAGICBOX_BUTTON_TIME);

        Timer 
            state_publish_timer (500);
    }

    /// Trigger components for the MagicBox
    namespace trig {
        FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, re_sw_ftrig;
        RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, re_sw_rtrig;
    }

    void mbcp_publish_state(MBCPState* state) {
        if (magicbox::remotes & (uint8_t)RemoteType::LoRa) {
            LoRa.beginPacket();
            LoRa.write((const uint8_t*)state, sizeof(MBCPState));
            LoRa.endPacket();
        }

        if (magicbox::remotes & (uint8_t)RemoteType::UDP) {
            udp.beginPacket(magicbox::UDP_TARGET_IP, magicbox::UDP_TARGET_PORT);
            udp.write((const uint8_t*)state, sizeof(MBCPState));
            udp.endPacket();
        }
    }

    /* Main functions */
        void setup() {
            // Inputs
            pinMode(MAGICBOX_PIN_BAT, INPUT);

            pinMode(MAGICBOX_PIN_JS_X, INPUT);
            pinMode(MAGICBOX_PIN_JS_Y, INPUT);
            pinMode(MAGICBOX_PIN_JS_SW, INPUT_PULLDOWN); 
            
            pinMode(MAGICBOX_PIN_BT_A1, INPUT_PULLDOWN);
            pinMode(MAGICBOX_PIN_BT_A2, INPUT_PULLDOWN);
            pinMode(MAGICBOX_PIN_BT_A3, INPUT_PULLDOWN);
            pinMode(MAGICBOX_PIN_BT_ULT, INPUT_PULLDOWN);

            pinMode(MAGICBOX_PIN_RE_DT, INPUT);     
            pinMode(MAGICBOX_PIN_RE_CL, INPUT);
            pinMode(MAGICBOX_PIN_RE_SW, INPUT);     // Integrated switch does not need pulldown

            // Outputs
            pinMode(MAGICBOX_PIN_BUZZER, OUTPUT);

            // LCD
            lcd.init();
            lcd.backlight();
        }

        void setup_lora(uint16_t sync_word) {
            if (magicbox::remotes & (uint8_t)RemoteType::LoRa) {
                log_errorln("> LoRa already initialized!");
                return;  
            }

            // LoRa
            LoRa.setPins(MAGICBOX_LORA_SS, MAGICBOX_LORA_RST, MAGICBOX_LORA_D0);
            LoRa.setTimeout(50);

            log_debug("> Setting up LoRa ");

            // Using american sender
            if (!LoRa.begin(433E6)) {   
                log_debug(".");
                delay(500);
            }

            LoRa.setSyncWord(sync_word);
            LoRa.setTxPower(MAGICBOX_MAX_LORA_POWER);
            log_debugln(" done!");

            if (magicbox::remotes == 0) {
                time::state_publish_timer.set();
            }

            magicbox::remotes |= (uint8_t)RemoteType::LoRa;
        }

        void setup_wifi(const char* ssid, const char* password) {
            log_debug("> Setting up WiFi ");
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid, password);

            while (WiFi.status() != WL_CONNECTED) {
                log_debug(".");
                delay(500);
            }

            log_debugln(" done!");
        }

        void setup_udp(const char* target_ip, uint16_t target_port, uint16_t own_port) {
            if (magicbox::remotes & (uint8_t)RemoteType::UDP) {
                log_errorln("> UDP already initialized!");
                return;  
            }
            
            log_debug("> Setting up UDP ");
            udp.begin(own_port);
            log_debugln(" done!");

            magicbox::UDP_TARGET_IP = target_ip;
            magicbox::UDP_TARGET_PORT = target_port;   

            if (magicbox::remotes == 0) {
                time::state_publish_timer.set();
            }

            magicbox::remotes |= (uint8_t)RemoteType::UDP;
        }

        void loop() {
            // ############
            // ## INPUTS ##
            // ############
            // Joystick
            // Reduce accuracy to 8 bit and remove default pos
            js_x = (int16_t)(analogRead(MAGICBOX_PIN_JS_X) >> 4) - (int16_t)MAGICBOX_JS_X_DEF;   
            js_y = (int16_t)(analogRead(MAGICBOX_PIN_JS_Y) >> 4) - (int16_t)MAGICBOX_JS_Y_DEF;   

            if (abs(js_x) > MAGICBOX_JS_MARGIN) {
                if (js_x > 0) {
                    js_coord_x = JoyStickCoord::Positive;
                } else {
                    js_coord_x = JoyStickCoord::Negative;
                }
            } else {
                js_coord_x = JoyStickCoord::None;
            }

            if (abs(js_y) > MAGICBOX_JS_MARGIN) {
                // Inverted for correct orientation
                if (js_y < 0) {
                    js_coord_y = JoyStickCoord::Positive;
                } else {
                    js_coord_y = JoyStickCoord::Negative;
                }
            } else {
                js_coord_y = JoyStickCoord::None;
            }

            if ((js_coord_x != JoyStickCoord::None) || (js_coord_y != JoyStickCoord::None)) {
                if (events.on_js_used) {
                    events.on_js_used(js_coord_x, js_coord_y);
                }
            }

            // Buttons
            js_sw_pressed = time::js_sw_toff(digitalRead(MAGICBOX_PIN_JS_SW));
            a1_pressed = time::a1_toff(digitalRead(MAGICBOX_PIN_BT_A1));
            a2_pressed = time::a2_toff(digitalRead(MAGICBOX_PIN_BT_A2));
            a3_pressed = time::a3_toff(digitalRead(MAGICBOX_PIN_BT_A3));
            ult_pressed = time::ult_toff(digitalRead(MAGICBOX_PIN_BT_ULT));

            // On pressed
            if (trig::js_sw_rtrig(js_sw_pressed)) {
                if (events.on_js_sw_pressed) {
                    events.on_js_sw_pressed();
                }
            }

            if (trig::a1_rtrig(a1_pressed)) {
                if (events.on_a1_pressed) {
                    events.on_a1_pressed();
                }
            }

            if (trig::a2_rtrig(a2_pressed)) {
                if (events.on_a2_pressed) {
                    events.on_a2_pressed();
                }
            }

            if (trig::a3_rtrig(a3_pressed)) {
                if (events.on_a3_pressed) {
                    events.on_a3_pressed();
                }
            }

            if (trig::ult_rtrig(ult_pressed)) {
                if (events.on_ult_pressed) {
                    events.on_ult_pressed();
                }
            }

            if (trig::re_sw_rtrig(time::re_sw_toff(encoder.check_switch()))) {
                if (events.on_encoder_sw_pressed) {
                    events.on_encoder_sw_pressed();
                }
            }

            // On release

            // Rotary encoder
            if (events.on_encoder_moved) {
                RotaryMove move = encoder.check_rotary();

                if (move == RotaryMove::CW) {
                    events.on_encoder_moved(encoder.counter, Direction::CW);
                } else if (move == RotaryMove::CCW) {
                    events.on_encoder_moved(encoder.counter, Direction::CCW);
                }
            }

            /* State Publishing */
            if (time::state_publish_timer.has_elapsed()) {
                MBCPState state = {
                    .button_states = (MBCPButtonStates)(
                        (a1_pressed << 0) |
                        (a2_pressed << 1) |
                        (a3_pressed << 2) |
                        (ult_pressed << 3) |
                        (re_sw_pressed << 4) |
                        (js_sw_pressed << 5)
                    ),
                    .rel_rot_val = encoder.counter,
                    .js_x_val = js_x,
                    .js_y_val = js_y
                };

                mbcp_publish_state(&state);
                time::state_publish_timer.set();
            }

            /* Other loops */
            magicbox::music::loop();
        }
    //
}