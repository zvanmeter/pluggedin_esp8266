#include <ESP8266WiFi.h>
#include "wifi_settings.h"

//Values defined in wifi_settings.h
const char* ssid = WIFI_SSID;
const char* ssid_password = WIFI_SECRET;

const int BOARD_LED_PIN = 2;
const int secondsBetweenLoops = 10;

void connectToWiFi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  
  WiFi.softAPdisconnect(true);
  WiFi.begin(ssid, ssid_password);
  
  turnOnBoardLed();
  while (WiFi.status() != WL_CONNECTED) {
    toggleBoardLed();
    delay(250);
    Serial.print(".");
  }
  turnOffBoardLed();
  
  Serial.println();
  Serial.print("WiFi connected, IP address: ");  
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  pinMode(BOARD_LED_PIN, OUTPUT);
  connectToWiFi();
}

void loop() {
  turnOnBoardLed();
  Serial.println("This page intentionally left blank.");
  turnOffBoardLed();
  delay(secondsBetweenLoops * 1000);
}

void turnOnBoardLed(){
  digitalWrite(BOARD_LED_PIN, LOW);
}

void turnOffBoardLed(){
  digitalWrite(BOARD_LED_PIN, HIGH);
}

void toggleBoardLed(){
  if (digitalRead(BOARD_LED_PIN)) {
    digitalWrite(BOARD_LED_PIN, LOW);
  } else {
    digitalWrite(BOARD_LED_PIN, HIGH);
  }
}

