#pragma once

#include <SPI.h>
#include <Ethernet.h>

// Set the MAC address and IP address for your Ethernet shield
extern const byte MAC[6];

// Define the endpoint and token
extern char* endpoint;
extern int port;
extern char* token;

#define RELAY 7

extern EthernetClient client;

int isValid(String idCard);
void gate(String ID);