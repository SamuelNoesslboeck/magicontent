# pragma once

# include <Arduino.h>
# include <LiquidCrystal_I2C.h>

// Sylo
# include <sylo/types.hpp>
# include <sylo/timing/toff.hpp>
# include <sylo/triggers/comp.hpp>
# include <sylo/triggers/ftrig.hpp>
# include <sylo/triggers/rtrig.hpp>
# include <sylo/components/rotary_encoder.hpp>

# include "defines.hpp"
# include "music.hpp"

namespace magicbox {
    enum class JoyStickCoord : int8_t {
        Positive = 1,
        None = 0,
        Negative = -1
    };

    enum class JoyStickState {
        None,
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW
    };

    typedef void (*ButtonEvent)();
    typedef void (*EncoderEvent)(int32_t, Direction);
    typedef void (*JoyStickEvent)(JoyStickCoord, JoyStickCoord);
    typedef void (*PotentioEvent)(uint16_t, int16_t);

    // Events
        static JoyStickEvent on_js_used = nullptr;
        static EncoderEvent on_encoder_moved = nullptr;
        
        // On-Press
        static ButtonEvent on_js_sw_pressed = nullptr;
        static ButtonEvent on_a1_pressed = nullptr;
        static ButtonEvent on_a2_pressed = nullptr;
        static ButtonEvent on_a3_pressed = nullptr;
        static ButtonEvent on_ult_pressed = nullptr;
        static ButtonEvent on_encoder_pressed = nullptr;

        // On-Release
        static ButtonEvent on_js_sw_released = nullptr;
        static ButtonEvent on_a1_released = nullptr;
        static ButtonEvent on_a2_released = nullptr;
        static ButtonEvent on_a3_released = nullptr;
        static ButtonEvent on_ult_released = nullptr;
        static ButtonEvent on_encoder_released = nullptr;
    //

    // Variables
        static bool js_sw_pressed = false;
        static bool a1_pressed = false;
        static bool a2_pressed = false;
        static bool a3_pressed = false;
        static bool ult_pressed = false;
        static bool encoder_pressed = false;

        static int16_t js_x, js_y;
        static JoyStickCoord js_coord_x, js_coord_y;
    // 

    // Objects
        static LiquidCrystal_I2C lcd(0x27, 16, 2);
        static RotaryEncoder encoder (MAGICBOX_PIN_RE_SW, MAGICBOX_PIN_RE_DT, MAGICBOX_PIN_RE_CL);
    // 

    /// Timer components for the MagicBox
    namespace time {
        static TOff 
            js_sw_toff (MAGICBOX_BUTTON_TIME), 
            a1_toff (MAGICBOX_BUTTON_TIME),
            a2_toff (MAGICBOX_BUTTON_TIME),
            a3_toff (MAGICBOX_BUTTON_TIME),
            ult_toff (MAGICBOX_BUTTON_TIME),
            encoder_toff (MAGICBOX_BUTTON_TIME);
    }

    /// Trigger components for the MagicBox
    namespace trig {
        static FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, encoder_ftrig;
        static RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, encoder_rtrig;
    }

    // Main events
        void setup() {
            // Setup pins
            // Inputs
            pinMode(MAGICBOX_PIN_BAT, INPUT);

            pinMode(MAGICBOX_PIN_JS_SW, INPUT);
            pinMode(MAGICBOX_PIN_JS_X, INPUT);
            pinMode(MAGICBOX_PIN_JS_Y, INPUT);
            
            pinMode(MAGICBOX_PIN_SW_A1, INPUT);
            pinMode(MAGICBOX_PIN_SW_A2, INPUT);
            pinMode(MAGICBOX_PIN_SW_A3, INPUT);
            pinMode(MAGICBOX_PIN_SW_ULT, INPUT);

            pinMode(MAGICBOX_PIN_RE_DT, INPUT);
            pinMode(MAGICBOX_PIN_RE_CL, INPUT);
            pinMode(MAGICBOX_PIN_RE_SW, INPUT);

            // Outputs
            pinMode(MAGICBOX_PIN_BUZZER, OUTPUT);

            // LCD
            lcd.init();
            lcd.backlight();
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
                if (on_js_used) {
                    on_js_used(js_coord_x, js_coord_y);
                }
            }

            // Buttons
            js_sw_pressed = time::js_sw_toff(digitalRead(MAGICBOX_PIN_JS_SW));
            a1_pressed = time::a1_toff(digitalRead(MAGICBOX_PIN_SW_A1));
            a2_pressed = time::a2_toff(digitalRead(MAGICBOX_PIN_SW_A2));
            a3_pressed = time::a3_toff(digitalRead(MAGICBOX_PIN_SW_A3));
            ult_pressed = time::ult_toff(digitalRead(MAGICBOX_PIN_SW_ULT));

            // On pressed
            if (trig::js_sw_rtrig(js_sw_pressed)) {
                if (on_js_sw_pressed) {
                    on_js_sw_pressed();
                }
            }

            if (trig::a1_rtrig(a1_pressed)) {
                if (on_a1_pressed) {
                    on_a1_pressed();
                }
            }

            if (trig::a2_rtrig(a2_pressed)) {
                if (on_a2_pressed) {
                    on_a2_pressed();
                }
            }

            if (trig::a3_rtrig(a3_pressed)) {
                if (on_a3_pressed) {
                    on_a3_pressed();
                }
            }

            if (trig::ult_rtrig(ult_pressed)) {
                if (on_ult_pressed) {
                    on_ult_pressed();
                }
            }

            // On release

            // Potentiometer
            if (on_encoder_moved) {
                RotaryMove move = encoder.check_rotary();

                if (move == RotaryMove::CW) {
                    on_encoder_moved(encoder.counter, Direction::CW);
                } else if (move == RotaryMove::CCW) {
                    on_encoder_moved(encoder.counter, Direction::CCW);
                }
            }

            if (trig::encoder_rtrig(time::encoder_toff(encoder.check_switch()))) {
                if (on_encoder_pressed) {
                    on_encoder_pressed();
                }
            }

            // Other loops
            magicbox::music::loop();
        }
    //
}