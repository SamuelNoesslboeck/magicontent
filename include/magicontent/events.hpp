# pragma once

# include <inttypes.h>

# include <sylo/types.hpp>

namespace magicbox {
    /// Indicates whether the a JoyStick-Coordinate (X/Y) is positive, negative or not moved at all
    enum class JoyStickCoord : int8_t {
        Positive = 1,
        None = 0,
        Negative = -1
    };

    /// Event for reiving a ping trace
    typedef void (*PingEvent)();
    /// Event for Button press & release
    typedef void (*ButtonEvent)();
    /// Event for movements of a rotary encoder
    typedef void (*EncoderEvent)(int32_t pos, Direction dir);
    /// Event for JoyStick-Movements
    typedef void (*JoyStickEvent)(JoyStickCoord x, JoyStickCoord y);
    /// Event for Potentiometer-Movements
    typedef void (*PotentioEvent)(uint16_t value, int16_t delta);

    /// Structure containing all the events for the MagicBox
    struct EventGroup {
        /// Event for reiving a ping trace from the controller/receiving device
        PingEvent on_ping = nullptr;

        /// Triggers each loop() iteration when the joystick is above the threshold positions
        JoyStickEvent on_js_used = nullptr;
        /// Triggers every time a difference in the encoder position has been recorded
        EncoderEvent on_encoder_moved = nullptr;
        
        // On-Press
        /// Triggers when the first ability switch has been pressed
        ButtonEvent on_a1_pressed = nullptr;
        /// Triggers when the second ability switch has been pressed
        ButtonEvent on_a2_pressed = nullptr;
        /// Triggers when the third ability switch has been pressed
        ButtonEvent on_a3_pressed = nullptr;
        /// Triggers when the ultimate ability switch has been pressed
        ButtonEvent on_ult_pressed = nullptr;
        /// Triggers when the encoder integrated switch has been pressed
        ButtonEvent on_encoder_pressed = nullptr;

        // On-Release
        /// Triggers when the first ability switch has been released
        ButtonEvent on_a1_released = nullptr;
        /// Triggers when the second ability switch has been released
        ButtonEvent on_a2_released = nullptr;
        /// Triggers when the third ability switch has been released
        ButtonEvent on_a3_released = nullptr;
        /// Triggers when the ultimate ability switch has been released
        ButtonEvent on_ult_released = nullptr;
        /// Triggers when the encoder integrated switch has been released
        ButtonEvent on_encoder_released = nullptr;
    };
}