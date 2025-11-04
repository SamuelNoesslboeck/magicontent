# include "magicontent/mbcp.hpp"

namespace magicbox {
    void parse_mbcp_msg(EventGroup* events, const uint8_t* msg_buffer, uint8_t msg_len) {
        if (msg_len == 0) {
            // Return error
        }

        MBCPMsgType msg_type = *(MBCPMsgType*)msg_buffer;

        // Check the message type and fire events accordingly
        if (msg_type == MBCPMsgType::None) {
            // Error
        } else if (msg_type == MBCPMsgType::ButtonPressed) {
            if (msg_len < (1 + sizeof(MBCPButtonMsg))) {
                // Error
            }

            MBCPButtonMsg msg = *(MBCPButtonMsg*)(msg_buffer + 1);

            if (msg.id == MBCPButtonID::AB1) {
                events->on_a1_pressed();
            } else if (msg.id == MBCPButtonID::AB2) {
                events->on_a2_pressed();
            } else if (msg.id == MBCPButtonID::AB3) {
                events->on_a3_pressed();
            } else if (msg.id == MBCPButtonID::ULT) {
                events->on_ult_pressed();
            } else if (msg.id == MBCPButtonID::RE) {
                events->on_encoder_pressed();
            } else {
                // Error
            }

        } else if (msg_type == MBCPMsgType::ButtonReleased) {

        } else if (msg_type == MBCPMsgType::JoyStick) {
            if (msg_len < (1 + sizeof(MBCPJoyStickMsg))) {
                // Error
            }

            MBCPJoyStickMsg msg = *(MBCPJoyStickMsg*)(msg_buffer + 1);

            events->on_js_used(msg.x, msg.y);

        } else if (msg_type == MBCPMsgType::Encoder) {
            if (msg_len < (1 + sizeof(MBCPEncoderMsg))) {
                // Error
            }

            MBCPEncoderMsg msg = *(MBCPEncoderMsg*)(msg_buffer + 1);

            events->on_encoder_moved(msg.pos, msg.dir);
        }
    }
}