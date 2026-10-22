// ###################################
// #    MAGICBOX - TESTING SKETCH    #
// ###################################
//
// A simple hardware testing sketch for the SpellBox controller

# include <LoRa.h>
# include <SPI.h>

# include <sylo/logging.hpp>

# define LOG_LEVEL LOG_LEVEL_TRACE

# include "magicontent/magicbox.hpp"
# include "magicontent/music.hpp"
# include "magicontent/mbcp.hpp"

// This file contains the WiFi credentials for the MagicBox controller and is not traced in git
# include "../keys/wifi_credentials.hpp"

# define UDP_TARGET_IP "192.168.178.20"

/* BUTTON EVENTS */
    void button_a1_pressed() {
        magicbox::lcd.setCursor(12, 1);
        magicbox::lcd.print('O');
    }

    void button_a1_released() {
        magicbox::lcd.setCursor(12, 1);
        magicbox::lcd.print(' ');
    }

    void button_a2_pressed() {
        magicbox::lcd.setCursor(12, 2);
        magicbox::lcd.print('O');
    }

    void button_a2_released() {
        magicbox::lcd.setCursor(12, 2);
        magicbox::lcd.print(' ');
    }

    void button_a3_pressed() {
        magicbox::lcd.setCursor(12, 3);
        magicbox::lcd.print('O');
    }

    void button_a3_released() {
        magicbox::lcd.setCursor(12, 3);
        magicbox::lcd.print(' ');
    }

    void button_ult_pressed() {
        magicbox::lcd.setCursor(13, 3);
        magicbox::lcd.print('O');
        magicbox::music::start_playing(
            &magicbox::music::melodies::BUTTON_ULT
        );
    }

    void button_ult_released() {
        magicbox::lcd.setCursor(13, 3);
        magicbox::lcd.print(' ');
    }
/**/

/* ROTARY ENCODER EVENTS */
    void button_re_pressed() {
        log_debugln("> Button RE pressed!");
    } 
/**/

/* JOYSTICK EVENTS */
    void button_js_sw_pressed() {
        magicbox::lcd.setCursor(18, 2);
        magicbox::lcd.print('O');
    }

    void button_js_sw_released() {
        magicbox::lcd.setCursor(18, 2);
        magicbox::lcd.print(' ');
    }

    void js_changed(magicbox::JoyStickCoord old_x, magicbox::JoyStickCoord old_y, magicbox::JoyStickCoord x, magicbox::JoyStickCoord y) {
        magicbox::lcd.setCursor(18 - (int8_t)old_y, 2 - (int8_t)old_x);    
        magicbox::lcd.print(' ');

        if (magicbox::js_active) {
            magicbox::lcd.setCursor(18 - (int8_t)y, 2 - (int8_t)x);
            magicbox::lcd.print('X');
        }
    }
/**/

void setup() {
    init_logging(115200);

    log_debugln("###################################"); 
    log_debugln("#    MAGICBOX - Testing sketch    #");
    log_debugln("###################################");
    log_debugln("");
    log_infoln("> Version: 2.1.0");
    log_debugln("");
    log_debugln("(c) Sy 2025  - CornerLab product");
    log_debugln("Helper sketch to test the functionality of the MagicBox controller");
    log_info("");
    
    // Setup controller
    magicbox::setup();

    // Events
    magicbox::events.on_a1_pressed = button_a1_pressed;
    magicbox::events.on_a2_pressed = button_a2_pressed;
    magicbox::events.on_a3_pressed = button_a3_pressed;
    magicbox::events.on_ult_pressed = button_ult_pressed;
    magicbox::events.on_encoder_sw_pressed = button_re_pressed;
    magicbox::events.on_js_sw_pressed = button_js_sw_pressed;

    magicbox::events.on_a1_released = button_a1_released;
    magicbox::events.on_a2_released = button_a2_released;
    magicbox::events.on_a3_released = button_a3_released;
    magicbox::events.on_ult_released = button_ult_released;
    magicbox::events.on_js_sw_released = button_js_sw_released;

    magicbox::events.on_js_changed = js_changed;

    // LCD    
    magicbox::lcd.backlight();
    magicbox::lcd.print("====  MagicBox  ====");

    // LoRa
    magicbox::setup_lora();     // Use default sync word (0xAA) for LoRa connection

    magicbox::lcd.setCursor(0, 1);
    magicbox::lcd.print("> LoRa OK");

    // WiFi + UDP
    magicbox::setup_wifi(WIFI_SSID, WIFI_PASSWORD);

    magicbox::lcd.setCursor(0, 2);
    magicbox::lcd.print("> WiFi OK");

    magicbox::setup_udp(UDP_TARGET_IP);

    magicbox::lcd.setCursor(0, 3);
    magicbox::lcd.print("> UDP  OK");

    
    magicbox::music::start_playing(&magicbox::music::melodies::STARTUP);
}

void loop() {
    magicbox::loop();
    delay(10);
}