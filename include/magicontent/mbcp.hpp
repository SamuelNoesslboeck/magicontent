# pragma once

# include <inttypes.h>
# include <sylo/types.hpp>

# include "events.hpp"

namespace magicbox {
    /// Defines whether the message is an IO-Event like a button press, a system message or etc.
    enum class MBCPMsgType : uint8_t {
        None = 0x00, 

        Ping,

        ButtonPressed, 
        ButtonReleased,
        JoyStick,
        Encoder
    };

    /// Defines IDs for the different buttons
    enum class MBCPButtonID : uint8_t {
        AB1 = 0x01,
        AB2 = 0x02,
        AB3 = 0x03,
        ULT = 0x0F, 
        RE = 0x11
    };

    /// Contents of a ping message
    struct MBCPPingMsg {
        uint8_t __placeholder;
    }; 

    /// Contents of a button type message
    struct MBCPButtonMsg {
        /// The ID of the button that is being pressed/released
        MBCPButtonID id;
    };

    /// Contents of a joystick type message
    struct MBCPJoyStickMsg {
        /// Coordinate value for X & Y
        JoyStickCoord x, y;
    };

    /// Contents of an encoder type message
    struct MBCPEncoderMsg {
        int32_t pos;
        Direction dir;
    };

    /// Parses an incoming MBCP message and fires events accordingly
    /// @param events The eventgroup with your custom events
    /// @param msg_buffer The byte-buffer of your incoming message
    /// @param msg_len The length of your incoming message
    void mbcp_parse_msg(EventGroup* events, const uint8_t* msg_buffer, uint8_t msg_len);
}