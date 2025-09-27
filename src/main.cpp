// ###################################
// #    MAGICBOX - TESTING SKETCH    #
// ###################################
//
// A simple hardware testing sketch for the SpellBox controller

# include <LoRa.h>
# include <SPI.h>

# include <sylo/logging.hpp>

# include "magicontent/magicbox.hpp"

# define LOG_LEVEL LOG_LEVEL_TRACE

/* BUTTON EVENTS */
/// @brief Event to be called on button presses
    void generic_button_event() {
        log_debugln("> Button pressed!");
    }

    void button_a1_pressed() {
        log_debugln("> Button A1 pressed!");
    }

    void button_a2_pressed() {
        log_debugln("> Button A2 pressed!");
    }

    void button_a3_pressed() {
        log_debugln("> Button A3 pressed!");
        log_trace("(X: ");
        log_trace(analogRead(MAGICBOX_PIN_JS_X));
        log_trace(", Y: ");
        log_trace(analogRead(MAGICBOX_PIN_JS_Y));
        log_trace(")");
        log_debug("\n");
    }

    void button_ult_pressed() {
        log_debugln("> Button ULT pressed!");
        log_trace("(X: ");
        log_trace(analogRead(MAGICBOX_PIN_JS_X));
        log_trace(", Y: ");
        log_trace(analogRead(MAGICBOX_PIN_JS_Y));
        log_trace(")");
        log_debug("\n");
    }
/**/

/// @brief Event to be called on movements of the rotary encoder
/// @param pos The new position of the encoder
/// @param dir The movement direction
void encoder_event(int32_t pos, Direction dir) {
    log_debug("> Encoder moved! ");
    log_trace("(POS: ");
    log_trace(pos);
    log_trace(", DIR: ");
    log_trace((bool)dir);
    log_trace(")");
    log_debug("\n");
}

/// @brief Event to be called on joystick movements
/// @param x The current X position
/// @param y The curernt Y position
void joystick_event(magicbox::JoyStickCoord x, magicbox::JoyStickCoord y) {
    log_debug("> Joystick active! ");
    log_trace("(X: ");
    log_trace((int8_t)x);
    log_trace(", Y: ");
    log_trace((int8_t)y);
    log_trace(")");
    log_debug("\n");
}

void setup() {
    init_logging(115200);

    log_debugln("###################################"); 
    log_debugln("#    MAGICBOX - Testing sketch    #");
    log_debugln("###################################");
    log_debugln("");
    log_infoln("> Version: 0.1.0");
    log_debugln("");
    log_debugln("(c) Sy 2025  - CornerLab product");
    log_debugln("Helper sketch to test the functionality of the MagicBox controller");
    log_info("");
    
    magicbox::setup();

    magicbox::on_js_used = joystick_event;
    magicbox::on_js_sw_pressed = generic_button_event;

    magicbox::on_a1_pressed = button_a1_pressed;
    magicbox::on_a2_pressed = button_a2_pressed;
    magicbox::on_a3_pressed = button_a3_pressed;
    magicbox::on_ult_pressed = button_ult_pressed;

    magicbox::on_encoder_moved = encoder_event;
    magicbox::on_encoder_pressed = generic_button_event;

    magicbox::lcd.backlight();
    magicbox::lcd.print("MagicBox");

    // Lora
    LoRa.setPins(MAGICBOX_LORA_SS, MAGICBOX_LORA_RST, MAGICBOX_LORA_D0);

    log_debug("> Setting up LoRa ");

    if (!LoRa.begin(433E6)) {   // Using american sender
        log_debug(".");
        delay(500);
    }

    LoRa.setSyncWord(0xAA);
    log_debugln(" done!");

    magicbox::lcd.setCursor(0, 1);
    magicbox::lcd.print("LoRa OK");
}

void loop() {
    magicbox::loop();
    delay(10);
}