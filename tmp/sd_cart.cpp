#include "sd_cart.hpp"

sdCart::sdCart() : timeClient(udp, "pool.ntp.org") {
  // this->timeClient(this->udp, "pool.ntp.org");
}

String const & sdCart::getEndpoint(void) const {
  return this->ENDPOINT;
}

String const & sdCart::getToken(void) const {
  return this->TOKEN;
}

bool sdCart::init(){

  bool res = false;
  SD.begin(SD_CART);
  // Check if the ".env" file exists
  if (SD.exists(".env")) {
    File envFile = SD.open(".env");
    // Serial.println("env Ok!!!");
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
          this->ENDPOINT = value;
        } else if (key == "token") {
          this->TOKEN = value;
        }
      }
    }
    envFile.close();
    res = true;
  }

  if (!SD.exists(LOG_FILE)) {
    File file = SD.open(LOG_FILE, O_CREAT | O_WRITE);
    if (file) {
      file.println("data_time,id,state");
      file.close();
    }
  }
  return res;
}

void sdCart::logData (const String & id, bool state) {

  File file = SD.open(LOG_FILE, O_APPEND);
  
  if (file) {
    // Format the log entry 
    // Get current date and time
    String logEntry = this->timeClient.getFormattedTime() + "," + id + ",";
    if (state)
      logEntry += "Access Granted";
    else
      logEntry += "Access Denied";
  
    // Append the log entry to the file
    file.println(logEntry);
    file.close();
  }
}
