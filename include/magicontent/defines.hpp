// #############################
// ##    MAGICBOX - DEFINES   ##
// #############################
//
// > Version 0.1.0

# pragma once

// Settings
/// @brief Minimum time between button signals to be registered as new events
# define MAGICBOX_BUTTON_TIME 50
/// @brief The sensitivity of the potentiometers
# define MAGICBOX_POT_SENS 20

/// @brief Minimum movement value until a joystick movement is tracked
# define MAGICBOX_JS_MARGIN 30
/// @brief Default value of the Joystick X-Coordinate when idle
# define MAGICBOX_JS_X_DEF 127
/// @brief Default value of the Joystick Y-Coordinate when idle
# define MAGICBOX_JS_Y_DEF 127

// ##############
// ##   PINS   ##
// ##############
// > For full reference, see the circuit diagram
    // Inputs
    /// @brief Pin to measure the battery voltage from
    # define MAGICBOX_PIN_BAT 0     // TODO: Add battery voltage measuring

    /// @brief Digital input of the joystick switch
    # define MAGICBOX_PIN_JS_SW 36
    /// @brief Analog value of the joystick in X direction
    # define MAGICBOX_PIN_JS_X 4
    /// @brief Analog value of the joystick in Y direction
    # define MAGICBOX_PIN_JS_Y 34

    /// @brief Digital input of the first action switch
    # define MAGICBOX_PIN_SW_A1 16
    /// @brief Digital input of the second action switch
    # define MAGICBOX_PIN_SW_A2 17
    /// @brief Digital input of the third action switch
    # define MAGICBOX_PIN_SW_A3 25
    /// @brief Digital input of the ultimate action switch
    # define MAGICBOX_PIN_SW_ULT 26

    /// @brief Digital input of the `DT` signal from the rotary encoder
    # define MAGICBOX_PIN_RE_DT 39
    /// @brief Digital input of the `CL` signal from the rotary encoder
    # define MAGICBOX_PIN_RE_CL 36
    /// @brief Digital input of the rotary encoder's switch
    # define MAGICBOX_PIN_RE_SW 13

    // Outputs
    /// @brief Pin of the buzzer element to play sounds from
    # define MAGICBOX_PIN_BUZZER 2
    
    // LoRa
    # define MAGICBOX_LORA_SS 5
    # define MAGICBOX_LORA_RST 14
    # define MAGICBOX_LORA_D0 27
//
