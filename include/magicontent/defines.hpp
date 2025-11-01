// #############################
// ##    MAGICBOX - DEFINES   ##
// #############################
//

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
// > For full reference, see the circuit diagram or the hardware reference
// <https://github.com/SamuelNoesslboeck/MagicBox/blob/master/documentation/hardware_reference.md>
    // Inputs
    /// @brief Pin to measure the battery voltage from
    # define MAGICBOX_PIN_BAT 0     // TODO: Add battery voltage measuring

    /// @brief Analog value of the joystick in X direction
    # define MAGICBOX_PIN_JS_X 4
    /// @brief Analog value of the joystick in Y direction
    # define MAGICBOX_PIN_JS_Y 34

    /// @brief Digital input of the first action button
    # define MAGICBOX_PIN_BT_A1 16
    /// @brief Digital input of the second action button
    # define MAGICBOX_PIN_BT_A2 17
    /// @brief Digital input of the third action button
    # define MAGICBOX_PIN_BT_A3 25
    /// @brief Digital input of the ultimate action button
    # define MAGICBOX_PIN_BT_ULT 26

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
    /// @brief Chip select Pin of the LoRa module
    # define MAGICBOX_LORA_SS 5
    /// @brief Reset pin of the LoRa module
    # define MAGICBOX_LORA_RST 14
    /// @brief The dataline of the LoRa module
    # define MAGICBOX_LORA_D0 27
//
