#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>

LED led(LED_PIN, LED_ACT);

void btnPush();
void btnDoubleClick();

OneButton button(BTN_PIN, !BTN_ACT);

void setup()
{
    led.off();

    // Single click -> ON/OFF
    button.attachClick(btnPush);

    // Double click -> Blink LED
    button.attachDoubleClick(btnDoubleClick);

    // Button timing
    button.setClickMs(250);
    button.setDebounceMs(50);

    Serial.begin(115200);
    Serial.println("OneButton Demo: Single=ON/OFF, Double=Blink");
}

void loop()
{
    led.loop();
    button.tick();
}

void btnPush()
{
    Serial.println("Single click - LED ON/OFF");
    led.flip();
}

void btnDoubleClick()
{
    Serial.println("Double click - LED blink");
    led.blink(200);
}