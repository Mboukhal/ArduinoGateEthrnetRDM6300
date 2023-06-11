#include "request.hpp"
#include <SoftwareSerial.h>

SoftwareSerial ssrfid = SoftwareSerial(3, -1);

const byte macAddress[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//        "http://192.168.1.20:8080/",            // endpoint

request network(

        "10.37.1.213",                           // hostname
        8080,                                     // port
        "/",                                      // uri
        "MyToken/00000000000000000000000000000",  // token
        macAddress,                               // mac address
        7                                         // relay pin
);

void setup() {


  Serial.begin(9600); 
  Serial.println("init serial..");

  // initialisation serial communication whit rfid
  ssrfid.begin(9600);
  ssrfid.listen();
  // Serial.println("init ssrfid..");

  // if (sd card return true(ref endpoint, ref token))
  // network.setConnectionInfo();

  // Serial.println("init network..");

  // initialisation of network communication
  network.init();

  Serial.println("init done.");

}


String id;

void loop() {

  // wait for data from rfid device
  if (ssrfid.available() > 0) {

    // read data from serial communivation from rfid device
    id = ssrfid.readStringUntil('\n');
    for ()
    Serial.println(id);
    // check for access and open gate
    network.gate(id);
    id = "";
    // flush serial communication
    while (ssrfid.available() > 0) {
      ssrfid.read();
    }
  }
}



