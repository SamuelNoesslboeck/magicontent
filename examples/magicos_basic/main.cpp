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

/* BUTTON EVENTS */
    void button_a1_pressed() {
        log_debugln("> Button A1 pressed!");
        magicbox::music::start_playing(
            &magicbox::music::melodies::BUTTON_A1
        );
    }

    void button_a2_pressed() {
        log_debugln("> Button A2 pressed!");
        magicbox::music::start_playing(
            &magicbox::music::melodies::BUTTON_A2
        );
    }

    void button_a3_pressed() {
        log_debugln("> Button A3 pressed!");
        magicbox::music::start_playing(
            &magicbox::music::melodies::BUTTON_A3
        );
    }

    void button_ult_pressed() {
        log_debugln("> Button ULT pressed!");
        magicbox::music::start_playing(
            &magicbox::music::melodies::BUTTON_ULT
        );

        // magicbox::MBCPButtonMsg msg = {
        //     magicbox::MBCPButtonID::ULT
        // };

        // LoRa.beginPacket();
        // LoRa.write((uint8_t)magicbox::MBCPMsgType::ButtonPressed);
        // LoRa.write((const uint8_t*)&msg, sizeof(magicbox::MBCPButtonMsg));
        // LoRa.endPacket();   
    }
/**/

/* ROTARY ENCODER EVENTS */
    void button_re_pressed() {
        log_debugln("> Button RE pressed!");
    } 
/**/

/* JOYSTICK EVENTS */
    void button_js_used() {
        log_debugln("> Button JS used!");
    }
/**/

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
    
    // Set integrated LoRa use to TRUE
    magicbox::setup(true);

    // Events
    magicbox::events.on_a1_pressed = button_a1_pressed;
    magicbox::events.on_a2_pressed = button_a2_pressed;
    magicbox::events.on_a3_pressed = button_a3_pressed;
    magicbox::events.on_ult_pressed = button_ult_pressed;

    magicbox::events.on_encoder_sw_pressed = button_re_pressed;

    magicbox::events.on_js_sw_pressed = button_js_used;

    // LCD    
    magicbox::lcd.backlight();
    magicbox::lcd.print("MagicBox");

    magicbox::music::start_playing(&magicbox::music::melodies::STARTUP);

    magicbox::lcd.setCursor(0, 1);
    magicbox::lcd.print("LoRa OK");
}

void loop() {
    magicbox::loop();
    delay(10);
}