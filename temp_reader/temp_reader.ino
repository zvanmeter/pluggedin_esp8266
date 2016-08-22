#include <DHT.h>
#include <ESP8266WiFi.h>
#include "wifi_settings.h"

//Values defined in wifi_settings.h
const char* ssid = WIFI_SSID;
const char* ssid_password = WIFI_SECRET;
const char* api_key = API_KEY;

const int BOARD_LED_PIN = 2;
const int DHT_PIN = 10;
const char DHT_SENSOR_TYPE = DHT22;
const bool getFahrenheit = true;
const int secondsBetweenReadings = 60;

DHT dht(DHT_PIN, DHT_SENSOR_TYPE);

float humidity;
float temperature;

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
  unsigned long runTimeStart = millis();
  turnOnBoardLed();
  readTempAndHumidity();
  printTempAndHumidity();
  uploadToThingSpeak();
  turnOffBoardLed();
  unsigned long runTimeEnd = millis();
  unsigned long runTimeDelta = runTimeEnd - runTimeStart;
  Serial.print(runTimeDelta/1000);
  Serial.println(" second loop run time");
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
  humidity = dht.readHumidity();
  temperature = dht.readTemperature(getFahrenheit);
}

void printTempAndHumidity() {
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" F");
}

void uploadToThingSpeak() {
  const int httpPort = 80;
  const char* hostUrl = "api.thingspeak.com";
  const String temperatureField = "field1";
  const String humidityField = "field2";

  WiFiClient client;
  if (!client.connect(hostUrl, httpPort)) {
    Serial.print("Connection to ");
    Serial.print(hostUrl);
    Serial.println(" failed!");
    return;
  }

  String url_parameters = "/update?";
         url_parameters += "api_key=";
         url_parameters += api_key;
         url_parameters +="&" + temperatureField + "=";
         url_parameters += temperature;
         url_parameters +="&" + humidityField + "=";
         url_parameters += humidity;

  Serial.print("Requesting URL: ");
  Serial.print(hostUrl);
  Serial.print(url_parameters);
  Serial.print(" ...");

  client.print("GET ");
  client.print(url_parameters);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(hostUrl);
  client.println("Connection: close");
  client.println();

  Serial.println(client.readStringUntil('\r'));
  client.stop();
}
