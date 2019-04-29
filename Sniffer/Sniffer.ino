#include<ESP8266WiFi.h>

const int working_channel = 1;
const uint8_t device_MAC[6] = {0x16, 0x34, 0x56, 0x78, 0x90, 0xab};
const uint8_t number_of_column = 8;

long packetCounter = 0;

void RecievePacket(unsigned char* pkt, short unsigned int i) {

  packetCounter++;
  int column_counter = 1;
  Serial.print("PACKET RECIEVED:");
  Serial.print(packetCounter);
  Serial.print("\n\n");

    for (int x = 0; x < i; x++) {
   

    char hexcode[1];
  if ((uint8_t) pkt[x] != 0) {

    sprintf(hexcode, "%0X", ((uint8_t)pkt[x]));

    if ((uint8_t)pkt[x] <= 0xf) {
      Serial.print("0");
      Serial.print(hexcode);
    }
    else {
      Serial.print(hexcode);
    }
    

    
  }
  else {
    Serial.print("00");
  }
    
  Serial.print(" ");
    

    if (column_counter == number_of_column) {
      column_counter = 0;
      Serial.println();
    }

    column_counter++;
    
  }

  for (int x = 0;x < 10;x++) { Serial.println(); } // Make a gap between Packets

  
  
}

void setup() {


  Serial.begin(921600);
  

  wifi_set_opmode(0x01);
  wifi_promiscuous_set_mac(device_MAC);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(RecievePacket);

}

void loop() {

}
