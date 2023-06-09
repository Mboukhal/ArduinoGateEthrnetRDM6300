#include "sd_cart.hpp"


void initSdCart() {
  SD.begin(SD_CART);

  // Check if the ".env" file exists
  if (SD.exists(".env")) {
    File envFile = SD.open(".env");
    
    while (envFile.available()) {
      String line = envFile.readStringUntil('\n');
      int separatorIndex = line.indexOf('=');
      
      if (separatorIndex != -1) {
        String key = line.substring(0, separatorIndex);
        String value = line.substring(separatorIndex + 1);
        
        value.trim();  // Remove leading/trailing whitespace
        
        // Remove double quotes if present
        if (value.startsWith("\"") && value.endsWith("\"")) {
          value = value.substring(1, value.length() - 1);
        }
        
        if (key == "endpoint") {
          ENDPOINT = value;
        } else if (key == "token") {
          TOKEN = value;
        }
      }
    }
    
    envFile.close();
  }

  if (!SD.exists(LOG_FILE)) {
    File file = SD.open(LOG_FILE, FILE_WRITE);
    file.println("data_time,id,state");
    file.close();
  }
}

void logData(const String& dataTime, const String& id, const String& state) {
  File file = SD.open(LOG_FILE, FILE_WRITE);
  
  if (file) {
    // Format the log entry
    String logEntry = dataTime + "," + id + "," + state;
  
    // Append the log entry to the file
    file.println(logEntry);
    file.close();
  }
}

void parseURL(String& hostname, String& uri, int& port) {
  
  int skip = 8;

  // No protocol identifier found, default to "http"
  port = 80;

  // Check if the URL starts with a protocol identifier
  if (url.startsWith("https://")) {
    port = 443;
  } else if (url.startsWith("http://")){
    skip--;
  } else {
    skip = 0;
  }

  // Remove the protocol from the URL
  String urlWithoutProtocol = url.substring(skip);

  // Find the hostname
  int hostnameEnd = urlWithoutProtocol.indexOf('/');
  if (hostnameEnd != -1) {
    // Extract the hostname
    hostname = urlWithoutProtocol.substring(0, hostnameEnd);

    // Find the URI
    uri = urlWithoutProtocol.substring(hostnameEnd);
  } else {
    // No URI found
    hostname = urlWithoutProtocol;
    uri = "/";
  }

  // Find the port number if specified
  int portStart = hostname.indexOf(':');
  if (portStart != -1) {
    hostname = hostname.substring(0, portStart);
    port = hostname.substring(portStart + 1).toInt();
  }
}
