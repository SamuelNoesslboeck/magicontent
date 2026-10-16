// #############################
// ##    MAGICBOX - DEFINES   ##
// #############################
//

# pragma once

// Settings
/// @brief Minimum time between button signals to be registered as new events
# define MAGICBOX_BUTTON_TIME 50

/// @brief Minimum movement value until a joystick movement is tracked
# define MAGICBOX_JS_MARGIN 30
/// @brief Default value of the Joystick X-Coordinate when idle
# define MAGICBOX_JS_X_DEF 127
/// @brief Default value of the Joystick Y-Coordinate when idle
# define MAGICBOX_JS_Y_DEF 127

/// @brief Maximum power for the LoRa module (in dBm)
# define MAGICBOX_MAX_LORA_POWER 18

// ##############
// ##   PINS   ##
// ##############
// > For full reference, see the circuit diagram or the hardware reference
// <https://github.com/SamuelNoesslboeck/MagicBox/blob/master/documentation/hardware_reference.md>
    // Inputs
    /// @brief Pin to measure the battery voltage from
    # define MAGICBOX_PIN_BAT 15     // TODO: Add battery voltage measuring

    /// @brief Analog value of the joystick in X direction
    # define MAGICBOX_PIN_JS_X 32
    /// @brief Analog value of the joystick in Y direction
    # define MAGICBOX_PIN_JS_Y 33
    /// @brief Digital input of the integrated switch of the joystick
    # define MAGICBOX_PIN_JS_SW 4

    /// @brief Digital input of the first action button
    # define MAGICBOX_PIN_BT_A1 35
    /// @brief Digital input of the second action button
    # define MAGICBOX_PIN_BT_A2 34
    /// @brief Digital input of the third action button
    # define MAGICBOX_PIN_BT_A3 36
    /// @brief Digital input of the ultimate action button
    # define MAGICBOX_PIN_BT_ULT 39

    /// @brief Digital input of the `DT` signal from the rotary encoder
    # define MAGICBOX_PIN_RE_DT 17
    /// @brief Digital input of the `CL` signal from the rotary encoder
    # define MAGICBOX_PIN_RE_CL 25
    /// @brief Digital input of the rotary encoder's switch
    # define MAGICBOX_PIN_RE_SW 26

    // Outputs
    /// @brief Pin of the buzzer element to play sounds from
    # define MAGICBOX_PIN_BUZZER 13
    
    // LoRa
    /// @brief Chip select Pin of the LoRa module
    # define MAGICBOX_LORA_SS 5
    /// @brief Reset pin of the LoRa module
    # define MAGICBOX_LORA_RST 27
    /// @brief The dataline of the LoRa module
    # define MAGICBOX_LORA_D0 16
//
