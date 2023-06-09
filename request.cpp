#include "request.hpp"

String ENDPOINT = "http://192.168.1.20:8080/";
String TOKEN = "your_token";

String hostname;
String uri;
int port;

const byte MAC[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

String setRequest(String data) {
  String header = "POST " + uri + " HTTP/1.1\n";
  header += "Host: " + hostname + "\n";
  header += "Connection: close\n";
  header += "Content-Type: application/x-www-form-urlencoded\n";
  header += "Content-Length: " + String(data.length()) + "\n\n";
  header += data;
  return header;
}

void gate(String id){
  if (Ethernet.linkStatus() == LinkOFF) {
  for (int i = 0; i < 20 && Ethernet.linkStatus() == LinkOFF; i++) {
    delay(500); // Wait for the Ethernet link to be restored
  }
  if (Ethernet.linkStatus() == LinkOFF) {
      Ethernet.begin(MAC);
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    delay(500); // Wait for the Ethernet link to be restored
  }
  // Perform your action here
  // For example, you can make an HTTP request or send a message
  }
  if (isValid(id)) {
    Serial.println("ID card is valid");
  } else {
    Serial.println("ID card is invalid");
  }
  delay(800);
}

int isValid(String idCard) {
  if (!hostname || !TOKEN) {
    Serial.println("Failed to load hostname or TOKEN variables.");
    return false;
  }

  // Prepare the data to be sent
  String data = "badge_id=" + idCard + "&target_token=" + TOKEN;

  // Make a POST request
  if (client.connect(hostname.c_str(), port)) {
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