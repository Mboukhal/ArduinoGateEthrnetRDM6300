#include "rfid.hpp"

// String id = "";

int buffer_index = 0;

SoftwareSerial ssrfid = SoftwareSerial(8, -1);

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame 


void rfidInit() {
  ssrfid.begin(9600);
  ssrfid.listen(); 
}
 
String extract_tag(uint8_t *buff) {

    String id;

    uint8_t *msg_data = buff + 1; // 10 byte => data contains 2byte version + 8byte tag
    buff = msg_data + 2;
    id = hexToDecimalString(buff, DATA_TAG_SIZE);
    return id;
}

String hexToDecimalString(char *str, unsigned int length) {
  
  String hexString;
  for ( int i = 0; i < length; i++ ) {
    hexString += str[i];
  }
  unsigned long decimalValue = strtoul(hexString.c_str(), NULL, 16);
  String decimalString = String(decimalValue);
  // Pad the decimal string with leading zeros if necessary
  while (decimalString.length() < 10) {
    decimalString = "0" + decimalString;
  }
  return decimalString;
}
