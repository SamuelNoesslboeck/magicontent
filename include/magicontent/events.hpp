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

    /// Event for Button press & release
    typedef void (*ButtonEvent)();
    /// Event for movements of a rotary encoder
    typedef void (*EncoderEvent)(int32_t pos, Direction dir);
    /// Event for JoyStick-Movements
    typedef void (*JoyStickEvent)(JoyStickCoord x, JoyStickCoord y);
    /// Event for Potentiometer-Movements
    typedef void (*PotentioEvent)(uint16_t value, int16_t delta);

    /// Structure containing all the events for the magicbox
    struct EventGroup {
        JoyStickEvent on_js_used = nullptr;
        EncoderEvent on_encoder_moved = nullptr;
        
        // On-Press
        ButtonEvent on_js_sw_pressed = nullptr;
        ButtonEvent on_a1_pressed = nullptr;
        ButtonEvent on_a2_pressed = nullptr;
        ButtonEvent on_a3_pressed = nullptr;
        ButtonEvent on_ult_pressed = nullptr;
        ButtonEvent on_encoder_pressed = nullptr;

        // On-Release
        ButtonEvent on_js_sw_released = nullptr;
        ButtonEvent on_a1_released = nullptr;
        ButtonEvent on_a2_released = nullptr;
        ButtonEvent on_a3_released = nullptr;
        ButtonEvent on_ult_released = nullptr;
        ButtonEvent on_encoder_released = nullptr;
    };
}