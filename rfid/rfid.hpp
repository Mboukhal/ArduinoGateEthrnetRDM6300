#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

// RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)bytes may vary)
#define BUFFER_SIZE 14
// 8byte tag
#define DATA_TAG_SIZE 8

// SoftwareSerial ssrfid = SoftwareSerial(8, -1);

class rfid {

  private:
    String id;
    SoftwareSerial ssrfid; 
    uint8_t buffer[BUFFER_SIZE];
    int buffer_index;

    bool call_extract_tag = false;
    int ssvalue = 0; 
    
    void hexToDecimalString(char *str, unsigned int length);
    void extract_tag();
    

  public:
    rfid(int RX, int TX);
    void init(void);
    bool waitForCart();
    String const & getId(void) const;

};




