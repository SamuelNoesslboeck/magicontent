# pragma once

# include <inttypes.h>
# include <sylo/types.hpp>

# include "events.hpp"

namespace magicbox {
    /* BUTTON STATES */
        /// Binary states of the buttons
        typedef uint8_t MBCPButtonStates;

        inline bool is_a1_pressed(MBCPButtonStates state) {
            return state & 0x01;
        }

        inline bool is_a2_pressed(MBCPButtonStates state) {
            return (state & 0x02) >> 1;
        }

        inline bool is_a3_pressed(MBCPButtonStates state) {
            return (state & 0x04) >> 2;
        }

        inline bool is_ult_pressed(MBCPButtonStates state) {
            return (state & 0x08) >> 3;
        }

        inline bool is_re_pressed(MBCPButtonStates state) {
            return (state & 0x10) >> 4;
        }

        inline bool is_js_pressed(MBCPButtonStates state) {
            return (state & 0x20) >> 5;
        }
    /**/

    /// Defines whether the message is an IO-Event like a button press, a system message or etc.
    struct MBCPState {
        MBCPButtonStates button_states;
        int8_t rel_rot_val;
        int8_t js_x_val;
        int8_t js_y_val;
    };

    /// Parses an incoming MBCP message and fires events accordingly
    /// @param events The eventgroup with your custom events
    /// @param msg_buffer The byte-buffer of your incoming message
    /// @param msg_len The length of your incoming message
    void mbcp_parse_msg(EventGroup* events, const uint8_t* msg_buffer, uint8_t msg_len);
}