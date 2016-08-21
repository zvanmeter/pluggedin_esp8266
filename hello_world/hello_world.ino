const int BOARD_LED_PIN = 2;
const int LED_FLASH_MILLISECONDS = 500;

void setup()
{
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello, world!");
}

void loop()
{
  Serial.println("Turning LED on.");
  digitalWrite(BOARD_LED_PIN, HIGH);
  delay(LED_FLASH_MILLISECONDS);
  Serial.println("Turning LED off.");
  digitalWrite(BOARD_LED_PIN, LOW);
  delay(LED_FLASH_MILLISECONDS);
}

