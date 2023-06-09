#pragma once

#include <SPI.h>
#include <Ethernet.h>

// Set the MAC address and IP address for your Ethernet shield
extern const byte MAC[6];

// Define the endpoint and token
extern String ENDPOINT;
extern String TOKEN;

extern String hostname;
extern String uri;
extern int port;

#define RELAY 7

extern EthernetClient client;

int isValid(String idCard);
void gate(String ID);