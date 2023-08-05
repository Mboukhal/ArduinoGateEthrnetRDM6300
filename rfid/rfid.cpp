#include "rfid.hpp"

rfid::rfid()
: ssrfid(8, -1) {}


rfid::rfid(int RX, int TX)
: ssrfid(RX, TX) {}

void rfid::init() {
  ssrfid.begin(9600);
  ssrfid.listen(); 
}
 
void rfid::extract_tag() {

  // String hexId;

  uint8_t *msg_data = buffer + 1; // 10 byte => data contains 2byte version + 8byte tag
  uint8_t *msg_data_version = msg_data;
  uint8_t *msg_data_tag = msg_data + 2;

  hexToDecimalString(msg_data_tag, DATA_TAG_SIZE);
}

String const & rfid::getId(void) const {
  return id;
}

// TODO: change char * by String
void rfid::hexToDecimalString(char *str, unsigned int length) {
  
  char hexString[length + 1];
  for ( int i = 0; i < length; i++ ) {
    hexString[i] = str[i];
  }
  unsigned long decimalValue = strtoul(hexString, NULL, 16);
  id = String(decimalValue);
  // Pad the decimal string with leading zeros if necessary
  while (id.length() < 10) {
    id = "0" + id;
  }
  ssrfid.println(id);
}

bool rfid::waitForCart(void) {
  
  if (ssrfid.available() > 0 ) {
    
    call_extract_tag = false; 
    ssvalue = 0; 
    ssvalue = ssrfid.read();  // read
    // if (ssvalue == -1) {
    //    // no data was read
    //    // TODO: log it
    //   return false;
    // }
    if (ssvalue == 2) {
       // RDM630/RDM6300 found a tag => tag incoming 
      buffer_index = 0;
    } else if (ssvalue == 3) { 
      // tag has been fully transmitted       
      call_extract_tag = true; 
      // extract tag at the end of the function call
    }
    // if (buffer_index >= BUFFER_SIZE) { 
    //   // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
    //   // TODO: log it
    //   // Serial.println("Error: Buffer overflow detected! ");
    //   return false;
    // }
    buffer[buffer_index++] = ssvalue;// everything is alright => copy current value to buffer
    if (call_extract_tag) {
      if (buffer_index == BUFFER_SIZE) {
        extract_tag();
        while (ssrfid.available() > 0) {
          ssrfid.read(); // read 
        }
        return true;
      } else {
        // something is wrong... start again looking for preamble (value: 2)
        buffer_index = 0;
        return false;
      }
    }  
  }
  return false;
}