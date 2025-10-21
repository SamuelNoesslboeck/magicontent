# include <LoRa.h>
# include <sylo/logging.hpp>

# define D0 17
# define SS 5
# define RST 14

void setup() {
    // LoRa
    LoRa.setPins(SS, RST, D0);

    log_debug("> Setting up LoRa ");

    // Using american sender
    if (!LoRa.begin(433E6)) {   
        log_debug(".");
        delay(500);
    }

    LoRa.setSyncWord(0xAA);
    log_debugln(" done!");
}

void loop() {
    int packetSize = LoRa.parsePacket();    // try to parse packet
    if (packetSize) 
    {
        Serial.print("Received packet '");
    
        while (LoRa.available())              // read packet
        {
            String LoRaData = LoRa.readString();
            Serial.print(LoRaData); 
        }
        Serial.print("' with RSSI ");         // print RSSI of packet
        Serial.println(LoRa.packetRssi());
    }
}