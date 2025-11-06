# pragma once

# include <inttypes.h> 

namespace magicbox {
    /// Different levels of signal quality, parsed from a RSSI value
    enum class SignalQuality {
        DISCONNECTED,
        BAD,
        POOR,
        GOOD,
        EXCELLENT
    };

    /// Helps tracking ping traces and active connections
    ///
    /// Pings should be started with your desired frequency and your desired method, then call `start_ping()`
    /// - If you call `finish_ping()` before the next `start_ping()`, the ping is seen as successful and the handler calculates ping and quality from your RSSI value
    /// - If `start_ping()` gets called again before calling `finish_ping()` the connection is seen as broken
    struct ConnHandler {
    private: 
        /// Whether or not a ping trace is currently ongoing
        bool pinging;
        uint32_t ping_stamp;

    public:
        /// Whether or not the last ping was succesful and the connection is therefore established
        bool connected;
        /// RSSI value of the last ping message
        int16_t rssi;
        /// Latency of the last ping message
        uint32_t ping;

        /// Parses a simplified `SignalQuality` value from the last RSSI value received
        SignalQuality quality();

        /// Starts a new ping trace, returns `false` if the last ping has not been successful
        bool start_ping();

        /// Finishes the ping trace with the given `rssi` value and calculates latency values out of it
        void finish_ping(int16_t rssi);
    };
}