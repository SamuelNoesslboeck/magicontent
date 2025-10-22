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

# include "events.hpp"

/// Collection of functions, datatypes and variables to utilize the MagicBox controller
namespace magicbox {
    /// General, internal events of the magicbox
    extern EventGroup events;

    // Variables
        /// Config variable whether or not to use library integrated LoRa
        extern bool integrated_lora;

        /// Whether the JoyStick-Switch is currently being pressed (not an event)
        extern bool js_sw_pressed;
        /// Whether the first ability switch is currently being pressed (not an event)
        extern bool a1_pressed;
        /// Whether the second ability switch is currently being pressed (not an event)
        extern bool a2_pressed;
        /// Whether the third ability switch is currently being pressed (not an event)
        extern bool a3_pressed;
        /// Whether the ultimate ability switch is currently being pressed (not an event)
        extern bool ult_pressed;
        /// Whether the encoder switch is currently being pressed (not an event)
        extern bool encoder_pressed;

        /// Raw input numbers of the JoyStick
        extern int16_t js_x, js_y;
        /// Fetched JoyStick Coordniates of the JoyStick
        extern JoyStickCoord js_coord_x, js_coord_y;
    // 

    // Objects
        /// Frontal LCD Display, controlled by I2C
        extern LiquidCrystal_I2C lcd;
        /// Rotary encoder on left side
        extern RotaryEncoder encoder;
    // 

    /// Timer components for the MagicBox
    namespace time {
        /// Internal TOff timers
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
        /// Falling trigger 
        extern FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, encoder_ftrig;
        extern RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, encoder_rtrig;
    }

    // Main events
        /// Setup all periphal devices and make the device operatable
        void setup(bool integrated_lora = false); 

        /// Processes IO and fires events accordingly, should be called very regularly
        void loop();
    //
}