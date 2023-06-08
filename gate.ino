#include "rfid.hpp"
#include "request.hpp"

void setup() {

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  Serial.begin(9600); 

  rfidInit();
  Ethernet.begin(MAC);

  // Print the assigned IP address
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());

  Serial.println("INIT DONE!");
}


void loop() {
  if (ssrfid.available() > 0 ) {
    getId();
  }
}

bool call_extract_tag = false;
int ssvalue = 0; // read 

void getId() {

    call_extract_tag = false; 
    ssvalue = ssrfid.read();  // read 
    if (ssvalue == -1) {
       // no data was read
      return;
    }
    if (ssvalue == 2) {
       // RDM630/RDM6300 found a tag => tag incoming 
      buffer_index = 0;
    } else if (ssvalue == 3) { 
      // tag has been fully transmitted       
      call_extract_tag = true; 
      // extract tag at the end of the function call
    }
    if (buffer_index >= BUFFER_SIZE) { 
      // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
      Serial.println("Error: Buffer overflow detected! ");
      return;
    }
    buffer[buffer_index++] = ssvalue;// everything is alright => copy current value to buffer
    if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        String id = extract_tag(buffer);
        Serial.println(id);
        gate(id);
        while (ssrfid.available() > 0) {
          ssvalue = ssrfid.read(); // read 
        }
      } else {
        // something is wrong... start again looking for preamble (value: 2)
        buffer_index = 0;
        return;
      }
    }  
}