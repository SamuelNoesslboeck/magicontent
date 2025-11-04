# include <LoRa.h>

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
    Serial.println(" done!");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}