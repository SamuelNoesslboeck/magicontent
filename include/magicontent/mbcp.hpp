# pragma once

# include <inttypes.h>
# include <sylo/types.hpp>

# include "magicbox.hpp"

namespace magicbox {
    enum class MBCPMsgType {
        None, 

        Ping,

        ButtonPressed, 
        ButtonReleased,
        JoyStick,
        Encoder
    };

    enum class MBCPButtonID : uint8_t {
        AB1,
        AB2,
        AB3,
        ULT, 
        JS,
        RE
    };

    struct MBCPButtonMsg {
        MBCPButtonID id;
    };

    struct MBCPJoyStickMsg {
        JoyStickCoord x, y;
    };

    struct MBCPEncoderMsg {
        int32_t pos;
        Direction dir;
    };
}