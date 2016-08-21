#include <ESP8266WiFi.h>
#include "wifi_settings.h"

//Values defined in wifi_setting.h
const char* ssid = WIFI_SSID;
const char* ssid_password = WIFI_SECRET;

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

