#include <gpio.c>

#define LED_PIN 0

int main(void)
{
    GPIO::setPin(LED_PIN, OUTPUT);

    while (1)
    {
        GPIO::write(LED_PIN, HIGH);
        delay(500);
        GPIO::write(LED_PIN, LOW);
        delay(500);
    }
}