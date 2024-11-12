#define BOARD_UNO
#include <CORE.c>

void setup(void)
{
    setPin(LED_BUILTIN, OUTPUT);
}

void update(void)
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}