#define LED_PIN12 12
#define LED_PIN13 13

// I just alternate lighting two LEDs!
void setup()
{
    pinMode(LED_PIN12, OUTPUT);
    pinMode(LED_PIN13, OUTPUT);
}

void loop()
{
    digitalWrite(LED_PIN12, HIGH);
    delay(100);
    digitalWrite(LED_PIN12, LOW);
    delay(900);
    digitalWrite(LED_PIN13, HIGH);
    delay(100);
    digitalWrite(LED_PIN13, LOW);
    delay(900);
}
