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

namespace magicbox {
    enum class JoyStickCoord : int8_t {
        Positive = 1,
        None = 0,
        Negative = -1
    };

    enum class JoyStickState : uint8_t {
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
        extern JoyStickEvent on_js_used;
        extern EncoderEvent on_encoder_moved;
        
        // On-Press
        extern ButtonEvent on_js_sw_pressed;
        extern ButtonEvent on_a1_pressed;
        extern ButtonEvent on_a2_pressed;
        extern ButtonEvent on_a3_pressed;
        extern ButtonEvent on_ult_pressed;
        extern ButtonEvent on_encoder_pressed;

        // On-Release
        extern ButtonEvent on_js_sw_released;
        extern ButtonEvent on_a1_released;
        extern ButtonEvent on_a2_released;
        extern ButtonEvent on_a3_released;
        extern ButtonEvent on_ult_released;
        extern ButtonEvent on_encoder_released;
    //

    // Variables
        extern bool integrated_lora;

        extern bool js_sw_pressed;
        extern bool a1_pressed;
        extern bool a2_pressed;
        extern bool a3_pressed;
        extern bool ult_pressed;
        extern bool encoder_pressed;

        extern int16_t js_x, js_y;
        extern JoyStickCoord js_coord_x, js_coord_y;
    // 

    // Objects
        extern LiquidCrystal_I2C lcd;
        extern RotaryEncoder encoder;
    // 

    /// Timer components for the MagicBox
    namespace time {
        extern TOff 
            js_sw_toff, 
            a1_toff,
            a2_toff,
            a3_toff ,
            ult_toff,
            encoder_toff;
    }

    /// Trigger components for the MagicBox
    namespace trig {
        extern FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, encoder_ftrig;
        extern RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, encoder_rtrig;
    }

    // Main events
        void setup(bool integrated_lora = false);

        // Setup pins
        void loop();
    //
}