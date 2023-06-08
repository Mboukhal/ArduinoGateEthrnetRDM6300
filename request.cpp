#include "request.hpp"

char* endpoint = "192.168.1.20";
int port = 8000;
char* token = "your_token";
const byte MAC[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

String setRequest(String data) {
  String header = "POST / HTTP/1.1\n";
  header += "Host: " + String(endpoint) + "\n";
  header += "Connection: close\n";
  header += "Content-Type: application/x-www-form-urlencoded\n";
  header += "Content-Length: " + String(data.length()) + "\n\n";
  header += data;
  return header;
}

void gate(String id){
  if (isValid(id)) {
    Serial.println("ID card is valid");
  } else {
    Serial.println("ID card is invalid");
  }
  delay(1000);
}

int isValid(String idCard) {
  if (!endpoint || !token) {
    Serial.println("Failed to load ENDPOINT or TOKEN variables.");
    return false;
  }

  // Prepare the data to be sent
  String data = "badge_id=" + idCard + "&target_token=" + token;

  // Make a POST request
  if (client.connect(endpoint, port)) {
    client.println(setRequest(data));
  } else {
    Serial.println("Failed to connect to the API server");
    return false;
  }

  // Read the response and check the status code
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String response = client.readStringUntil('\n');
  client.stop();

  if (response.indexOf("200 OK") != -1) {
    return true;
  }

  return false;
}