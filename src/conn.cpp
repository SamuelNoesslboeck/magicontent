# include "magicontent/conn.hpp"

# include <Arduino.h>

namespace magicbox {
    SignalQuality ConnHandler::quality() {
        if (!this->connected) {
            return SignalQuality::DISCONNECTED;
        }

        if (this->rssi < (-100)) {
            return SignalQuality::DISCONNECTED;
        } else if (this->rssi < (-90)) {
            return SignalQuality::BAD;
        } else if (this->rssi < (-80)) {
            return SignalQuality::POOR;
        } else if (this->rssi < (-70)) {
            return SignalQuality::GOOD;
        } else {
            return SignalQuality::EXCELLENT;
        }
    }

    bool ConnHandler::start_ping() {
        if (this->pinging) {
            // Error, already pinging, last one didn't come through => Set status to disconnected
            this->connected = false;
            this->rssi = INT16_MIN;
            this->ping = UINT32_MAX;
            return false;
        }

        // Update ping stamp to current time and start pinging
        this->ping_stamp = millis();
        this->pinging = true;

        return true;
    }

    void ConnHandler::finish_ping(int16_t rssi) {
        if (!this->pinging) {
            // Error, no ping has been started yet
            return;
        }

        this->pinging = false;

        this->rssi = rssi;
        this->ping = (millis() - this->ping_stamp) / 2;     // Ping message travels twice
    }
}