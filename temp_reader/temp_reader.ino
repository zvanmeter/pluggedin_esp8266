#include <ESP8266WiFi.h>

const char* ssid = "TheForgeGuest";
const char* ssid_password = "n0c0nstraints!";

void connectToWiFi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  
  WiFi.begin(ssid, ssid_password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("WiFi connected, IP address: ");  
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  Serial.println("This page intentionally left blank.");
  delay(10000);
}

