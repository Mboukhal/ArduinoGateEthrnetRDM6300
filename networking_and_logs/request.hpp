#pragma once

#include <SPI.h>
#include <Ethernet.h>
// #include <HttpClient.h>

#define DELAY_OPENING_GATE 800

class request {

  private:
      // Set the MAC address and IP address for your Ethernet shield
    const byte MAC[6] =  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

      // Define the endpoint and token
    String  TOKEN;
    String  ENDPOINT;

    String  HostName;
    String  Uri;
    int     Port;
    String  header;

    int RELAY;

    EthernetClient client;
    // void parseURL();
    bool isValid(String const & idCart);

  public:
    request(String const &, int, String const &, String const &, const byte*, int);
    void init(void);
    void gate(String const & id);

};
