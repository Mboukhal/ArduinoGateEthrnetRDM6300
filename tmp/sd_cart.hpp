#pragma once


#include "request.hpp"
#include <NTPClient.h>
#include <SD.h>

#define SD_CART 4
#define LOG_FILE "LOG.CSV"

class sdCart {

  private:
    String ENDPOINT;
    String TOKEN;
    EthernetUDP udp;
    NTPClient timeClient;

  public:
    sdCart();
    bool init(); // true if .env existed
    void logData(const String& id, bool state);
    String const & getEndpoint(void) const;
    String const & getToken(void) const;
};
