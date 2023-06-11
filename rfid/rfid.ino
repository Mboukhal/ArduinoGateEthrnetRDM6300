#include "rfid.hpp"


rfid reader(8, 3);

void setup() {

  reader.init();
  
  Serial.begin(9600); 
  Serial.println("\ninit serial..");
}

void loop() {

  if (reader.waitForCart()) {

    reader.getId();
  }
}