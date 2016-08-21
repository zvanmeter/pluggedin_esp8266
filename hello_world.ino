const int BOARD_LED_PIN = 2;
const int LED_FLASH_MILLISECONDS = 500;

void setup()
{
  pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(BOARD_LED_PIN, HIGH);
  delay(LED_FLASH_MILLISECONDS);
  digitalWrite(BOARD_LED_PIN, LOW);
  delay(LED_FLASH_MILLISECONDS);
}

