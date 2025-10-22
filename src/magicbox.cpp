# pragma once

# include <Arduino.h>
# include <LiquidCrystal_I2C.h>
# include <LoRa.h>

// Sylo
# include <sylo/logging.hpp>

# include "magicontent/defines.hpp"
# include "magicontent/mbcp.hpp"
# include "magicontent/music.hpp"
# include "magicontent/magicbox.hpp"

namespace magicbox {
    // Events
        /// Internal events used when overriding the controller
        EventGroup group;
    //

    // Variables
        bool integrated_lora = false;

        bool js_sw_pressed = false;
        bool a1_pressed = false;
        bool a2_pressed = false;
        bool a3_pressed = false;
        bool ult_pressed = false;
        bool encoder_pressed = false;

        int16_t js_x, js_y;
        JoyStickCoord js_coord_x, js_coord_y;
    // 

    // Objects
        LiquidCrystal_I2C lcd(0x27, 16, 2);
        RotaryEncoder encoder (MAGICBOX_PIN_RE_SW, MAGICBOX_PIN_RE_DT, MAGICBOX_PIN_RE_CL);
    // 

    /// Timer components for the MagicBox
    namespace time {
        TOff 
            js_sw_toff (MAGICBOX_BUTTON_TIME), 
            a1_toff (MAGICBOX_BUTTON_TIME),
            a2_toff (MAGICBOX_BUTTON_TIME),
            a3_toff (MAGICBOX_BUTTON_TIME),
            ult_toff (MAGICBOX_BUTTON_TIME),
            encoder_toff (MAGICBOX_BUTTON_TIME);
    }

    /// Trigger components for the MagicBox
    namespace trig {
        FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, encoder_ftrig;
        RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, encoder_rtrig;
    }

    template<typename T>
    void mbcp_send_msg(MBCPMsgType type, const T* obj) {
        LoRa.beginPacket();
        LoRa.write((uint8_t)type);
        LoRa.write((const uint8_t*)obj, sizeof(T));
        LoRa.endPacket();
    }

    // Main events
        void setup(bool integrated_lora) {
            // Setup pins
            // Inputs
            pinMode(MAGICBOX_PIN_BAT, INPUT);

            pinMode(MAGICBOX_PIN_JS_SW, INPUT);
            pinMode(MAGICBOX_PIN_JS_X, INPUT);
            pinMode(MAGICBOX_PIN_JS_Y, INPUT);
            
            pinMode(MAGICBOX_PIN_BT_A1, INPUT);
            pinMode(MAGICBOX_PIN_BT_A2, INPUT);
            pinMode(MAGICBOX_PIN_BT_A3, INPUT);
            pinMode(MAGICBOX_PIN_BT_ULT, INPUT);

            pinMode(MAGICBOX_PIN_RE_DT, INPUT);
            pinMode(MAGICBOX_PIN_RE_CL, INPUT);
            pinMode(MAGICBOX_PIN_RE_SW, INPUT);

            // Outputs
            pinMode(MAGICBOX_PIN_BUZZER, OUTPUT);

            // LCD
            lcd.init();
            lcd.backlight();

            magicbox::integrated_lora = integrated_lora;

            // LoRa
            LoRa.setPins(MAGICBOX_LORA_SS, MAGICBOX_LORA_RST, MAGICBOX_LORA_D0);

            log_debug("> Setting up LoRa ");

            // Using american sender
            if (!LoRa.begin(433E6)) {   
                log_debug(".");
                delay(500);
            }

            LoRa.setSyncWord(0xAA);
            log_debugln(" done!");
        }

        void loop() {
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

            // Buttons
            if ((js_coord_x != JoyStickCoord::None) || (js_coord_y != JoyStickCoord::None)) {
                if (events.on_js_used) {
                    events.on_js_used(js_coord_x, js_coord_y);
                }

                if (integrated_lora) {
                    const MBCPJoyStickMsg msg = MBCPJoyStickMsg {
                        js_coord_x, js_coord_y
                    };
                    mbcp_send_msg(MBCPMsgType::JoyStick, &msg);
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

                if (integrated_lora) {
                    const MBCPButtonMsg msg = MBCPButtonMsg {
                        MBCPButtonID::JS
                    };
                    mbcp_send_msg(MBCPMsgType::ButtonPressed, &msg);
                }
            }

            if (trig::a1_rtrig(a1_pressed)) {
                if (events.on_a1_pressed) {
                    events.on_a1_pressed();
                }

                if (integrated_lora) {
                    const MBCPButtonMsg msg = MBCPButtonMsg {
                        MBCPButtonID::AB1
                    };
                    mbcp_send_msg(MBCPMsgType::ButtonPressed, &msg);
                }
            }

            if (trig::a2_rtrig(a2_pressed)) {
                if (events.on_a2_pressed) {
                    events.on_a2_pressed();
                }

                if (integrated_lora) {
                    const MBCPButtonMsg msg = MBCPButtonMsg {
                        MBCPButtonID::AB2
                    };
                    mbcp_send_msg(MBCPMsgType::ButtonPressed, &msg);
                }
            }

            if (trig::a3_rtrig(a3_pressed)) {
                if (events.on_a3_pressed) {
                    events.on_a3_pressed();
                }


                if (integrated_lora) {
                    const MBCPButtonMsg msg = MBCPButtonMsg {
                        MBCPButtonID::AB3
                    };
                    mbcp_send_msg(MBCPMsgType::ButtonPressed, &msg);
                }
            }

            if (trig::ult_rtrig(ult_pressed)) {
                if (events.on_ult_pressed) {
                    events.on_ult_pressed();
                }

                if (integrated_lora) {
                    const MBCPButtonMsg msg = MBCPButtonMsg {
                        MBCPButtonID::ULT
                    };
                    mbcp_send_msg(MBCPMsgType::ButtonPressed, &msg);
                }
            }

            // On release

            // Potentiometer
            if (events.on_encoder_moved) {
                RotaryMove move = encoder.check_rotary();

                if (move == RotaryMove::CW) {
                    events.on_encoder_moved(encoder.counter, Direction::CW);
                } else if (move == RotaryMove::CCW) {
                    events.on_encoder_moved(encoder.counter, Direction::CCW);
                }
            }

            if (trig::encoder_rtrig(time::encoder_toff(encoder.check_switch()))) {
                if (events.on_encoder_pressed) {
                    events.on_encoder_pressed();
                }
            }

            // Other loops
            magicbox::music::loop();
        }
    //
}