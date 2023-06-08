#pragma once

#include <Arduino.h>

#include <SoftwareSerial.h>

// RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)bytes may vary)
#define BUFFER_SIZE 14
// 8byte tag
#define DATA_TAG_SIZE 8

// SoftwareSerial ssrfid = SoftwareSerial(8, -1);

extern SoftwareSerial ssrfid; 

extern uint8_t buffer[BUFFER_SIZE];

extern int buffer_index;

#define INTERRAPT 2

// extern String id;

void rfidInit();

String hexToDecimalString(char *str, unsigned int length);

String extract_tag(uint8_t *buff);

