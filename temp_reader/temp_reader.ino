#include <DHT.h>
#include <ESP8266WiFi.h>
#include "wifi_settings.h"

//Values defined in wifi_settings.h
const char* ssid = WIFI_SSID;
const char* ssid_password = WIFI_SECRET;

const int BOARD_LED_PIN = 2;
const int DHT_PIN = 10;
const char DHT_SENSOR_TYPE = DHT22;
const bool getFahrenheit = true;
const int secondsBetweenReadings = 20;

DHT dht(DHT_PIN, DHT_SENSOR_TYPE);

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
  dht.begin();
}

void loop() {
  turnOnBoardLed();
  readTempAndHumidity();
  turnOffBoardLed();
  delay(secondsBetweenReadings * 1000);
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

void readTempAndHumidity(){
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(getFahrenheit);
  printTempAndHumidity(temperature, humidity);
}

void printTempAndHumidity(float temperature, float humidity) {
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" F");
}
