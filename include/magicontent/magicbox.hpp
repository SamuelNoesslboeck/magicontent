# pragma once

# include <Arduino.h>
# include <LiquidCrystal_I2C.h>
# include <WiFiUdp.h>

// Sylo
# include <sylo/types.hpp>
# include <sylo/timing/timer.hpp>
# include <sylo/timing/toff.hpp>
# include <sylo/triggers/comp.hpp>
# include <sylo/triggers/ftrig.hpp>
# include <sylo/triggers/rtrig.hpp>
# include <sylo/components/rotary_encoder.hpp>

# include "defines.hpp"
# include "events.hpp"
# include "mbcp.hpp"

/// Collection of functions, datatypes and variables to utilize the MagicBox controller
namespace magicbox {
    /// Different types of active remotes that can be used with the MagicBox
    enum class RemoteType : uint8_t {
        LoRa = 0x01,
        UDP = 0x02
    };

    /// General, internal events of the magicbox
    extern EventGroup events;

    // Variables
        /// Currently enabled remotes, see `RemoteType` for more information
        extern uint8_t remotes;

        /// Whether the JoyStick-Switch is currently being pressed (not an event)
        extern bool js_sw_active;
        /// Whether the first ability switch is currently being pressed (not an event)
        extern bool a1_active;
        /// Whether the second ability switch is currently being pressed (not an event)
        extern bool a2_active;
        /// Whether the third ability switch is currently being pressed (not an event)
        extern bool a3_active;
        /// Whether the ultimate ability switch is currently being pressed (not an event)
        extern bool ult_active;
        /// Whether the rotary encoder switch is currently being pressed (not an event)
        extern bool re_sw_active;
        /// Whether or not the joystick is being used
        extern bool js_active;

        /// Raw input numbers of the JoyStick
        extern int16_t js_x, js_y;
        /// Fetched JoyStick Coordniates of the JoyStick
        extern JoyStickCoord js_coord_x, js_coord_y;
    // 

    /* Configs */
        /// Target IP for UDP connections
        extern const char* UDP_TARGET_IP;
        /// Target port for UDP connections
        extern uint16_t UDP_TARGET_PORT;
    /**/

    // Objects
        /// Frontal LCD Display, controlled by I2C
        extern LiquidCrystal_I2C lcd;
        /// Rotary encoder on left side
        extern RotaryEncoder encoder;
        /// UDP object for UDP connections
        extern WiFiUDP udp;
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
            re_sw_toff;

        /// Internal timer for ping tracing
        extern Timer 
            state_publish_timer;
    }

    /// Trigger components for the MagicBox
    namespace trig {
        /// Falling trigger 
        extern FTrig js_sw_ftrig, a1_ftrig, a2_ftrig, a3_ftrig, ult_ftrig, re_sw_ftrig;
        extern RTrig js_sw_rtrig, a1_rtrig, a2_rtrig, a3_rtrig, ult_rtrig, re_sw_rtrig;
    }

    /// Publishes a MBCP state to all enabled remotes
    void mbcp_publish_state(MBCPState* state);

    /* Main functions */
        /// Setup all periphal devices and make the device operatable
        void setup(); 

        /// Sets up the LoRa module and enables it for usage, specifying the sync word for the LoRa connection
        /// @param sync_word The LoRa sync word to be used for the connection, default is `0xAA`
        void setup_lora(uint16_t sync_word = 0xAA);

        /// Sets up the WiFi connection and enables it for usage, specifying the SSID and password of the network
        void setup_wifi(const char* ssid, const char* password);

        /// Sets up the UDP connection and enables it for usage, specifying the port to be used  
        /// Remember to call `setup_wifi()` before calling this function, otherwise the UDP connection will not work!
        void setup_udp(const char* target_ip, uint16_t target_port = MAGICBOX_DEFAULT_PORT, uint16_t own_port = MAGICBOX_DEFAULT_PORT);

        /// Processes IO and fires events accordingly, should be called very regularly
        void loop();
    /**/
}