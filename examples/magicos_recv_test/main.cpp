# include <LoRa.h>
# include <magicontent/mbcp.hpp>

# define LORA_SS 5
# define LORA_RST 14
# define LORA_D0 17

void setup() {
    Serial.begin(115200);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_D0);

    // Using american sender
    if (!LoRa.begin(433E6)) {   
        Serial.print(".");
        delay(500);
    }

    LoRa.setSyncWord(0xAA);
    LoRa.setTimeout(50);
    Serial.println(" done!");
}

uint8_t LoRaData [64];

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet with length ");

    // read packet
    while (LoRa.available()) {
      uint8_t msg_len = LoRa.readBytes(LoRaData, 64);
      Serial.print((int)msg_len);

      if ((magicbox::MBCPMsgType)(LoRaData[0]) == magicbox::MBCPMsgType::Ping) {
        LoRa.beginPacket();
        LoRa.write((uint8_t)magicbox::MBCPMsgType::Ping);
        LoRa.endPacket();
        Serial.print(" (ping request)");
      }
    }

    // print RSSI of packet
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}