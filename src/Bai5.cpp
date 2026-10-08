#include <Arduino.h>
#include <OneButton.h>


#define LED1_PIN 2       // LED built-in trên ESP32
#define LED2_PIN 4       // LED ngoài
#define BUTTON_PIN 18    // Nút nhấn mới

// =============================
// Khởi tạo OneButton
// =============================

// true: nút nhấn active LOW
// Vì nút được nối giữa GPIO18 và GND
OneButton button(BUTTON_PIN, true);

// LED đang được điều khiển
// 1 = LED1
// 2 = LED2
int selectedLED = 1;

// Trạng thái LED
bool led1State = false;
bool led2State = false;

// Thời gian blink
unsigned long previousMillis = 0;

// Trạng thái blink
bool blinking = false;



void singleClick();
void doubleClick();
void longPressStart();
void longPressStop();

void setSelectedLED(bool state);
void toggleSelectedLED();



void setup()
{
    Serial.begin(115200);

    // Cấu hình LED
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    // Tắt cả hai LED lúc khởi động
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

    // Cấu hình nút nhấn
    button.attachClick(singleClick);
    button.attachDoubleClick(doubleClick);

    // Giữ nút để bắt đầu blink
    button.attachLongPressStart(longPressStart);

    // Thả nút để dừng blink
    button.attachLongPressStop(longPressStop);

    // Thời gian nhận diện click
    button.setClickMs(250);

  
    button.setDebounceMs(50);



void loop()
{
    // Cập nhật trạng thái nút
    button.tick();

    // Xử lý blink
    if (blinking)
    {
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= 200)
        {
            previousMillis = currentMillis;

            // Đảo trạng thái LED đang được chọn
            if (selectedLED == 1)
            {
                led1State = !led1State;
                digitalWrite(LED1_PIN, led1State);
            }
            else
            {
                led2State = !led2State;
                digitalWrite(LED2_PIN, led2State);
            }
        }
    }
}



void singleClick()
{
    Serial.println("Single click -> Toggle selected LED");

    toggleSelectedLED();
}



void doubleClick()
{
    // Chuyển LED đang điều khiển
    if (selectedLED == 1)
    {
        selectedLED = 2;
        Serial.println("Double click -> Selected LED2");
    }
    else
    {
        selectedLED = 1;
        Serial.println("Double click -> Selected LED1");
    }
}



void longPressStart()
{
    Serial.println("Long press -> Start blinking");

    blinking = true;

    // Bắt đầu tính thời gian blink
    previousMillis = millis();
}



void longPressStop()
{
    Serial.println("Long press -> Stop blinking");

    blinking = false;
}



void toggleSelectedLED()
{
    if (selectedLED == 1)
    {
        led1State = !led1State;
        digitalWrite(LED1_PIN, led1State);

        Serial.print("LED1 -> ");
        Serial.println(led1State ? "ON" : "OFF");
    }
    else
    {
        led2State = !led2State;
        digitalWrite(LED2_PIN, led2State);

        Serial.print("LED2 -> ");
        Serial.println(led2State ? "ON" : "OFF");
    }
}