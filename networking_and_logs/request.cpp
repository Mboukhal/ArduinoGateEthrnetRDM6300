#include "request.hpp"

request::request(String const & hostname, int port, String const & uri, String const & token, const byte * macAddress, int relay = 7)
: HostName(hostname), Uri(uri), Port(port), TOKEN(token), RELAY(relay) {
  memcpy(MAC, macAddress, 6);
}

void request::init() {

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  this->header = "POST " + this->Uri + " HTTP/1.1\n";
  this->header += "Host: " + this->HostName + ":" + String(this->Port) + "\n";
  this->header += "Connection: close\n";
  this->header += "Content-Type: application/x-www-form-urlencoded\n";
  this->header += "Content-Length: ";
  // this->header += String(data.length()) + "\n\n" + data;
  
  Ethernet.begin(MAC);
}

void request::gate(String const & id){
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
  isValid(id);
  // if (isValid(id)) {
  //   // TODO: log Access Granted
  //   // Serial.println("ID card is valid");
  // } else {
  //   // Serial.println("ID card is invalid");
  // }
  // delay(800);
}

bool request::isValid(String const & idCart) {
  Serial.print("OK: ");
  Serial.println(idCart);
  if (!this->HostName || !this->TOKEN) {
    // TODO: log and set fatal error
    // Serial.println("Failed to load hostname or TOKEN variables.");
    return false;
  }

  // Prepare the data to be sent
  String data = "badge_id=" + idCart + "&target_token=" + this->TOKEN;

  // Make a POST request
  if (this->client.connect(this->HostName.c_str(), this->Port)) {
    this->client.print(this->header);
    this->client.println(String(data.length()));
    this->client.println();
    this->client.println(data);
  } else {
    // TODO: log and check connection
    // Serial.println("Failed to connect to the API server");
    return false;
  }
  
  Serial.print("OK: ");
  Serial.println(data);

  // Read the response and check the status code
  while (this->client.connected()) {

    data = this->client.readStringUntil('\n');
    if (data == "\r") {
      break;
    }
  }
  data = this->client.readStringUntil('\n');
  this->client.stop();

  if (data.indexOf("200 OK") != -1) {
    digitalWrite(RELAY, HIGH);
    delay(DELAY_OPENING_GATE);
    digitalWrite(RELAY, LOW);
    return true;
  }
  return false;
}

