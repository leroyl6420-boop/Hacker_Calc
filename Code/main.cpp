#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include <cstdio>

int main() {
    //Components
    const uint BUTTON1 = 0;
    const uint SDA = 6;
    const uint SCL = 7;

    const uint8_t OLED_ADDR = 0x3C;

    //Debounce
    const uint DEBOUNCE = 50;
    int lastReading = 1;
    int buttonState = 1;
    uint64_t lastChange = 0;
    uint64_t lastConfirmedPress = 0;
    uint64_t lastConfirmedRelease = 0;

    //Variables
    int morse[5]; 
    int morsePause = 500;
    int morseValue = 0;
    int number[10];
    int numberValue = 0;
    char text[20];

    i2c_init(i2c1, 100000);
    gpio_init(BUTTON1);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);


    gpio_set_dir(BUTTON1, GPIO_IN);

    gpio_pull_up(BUTTON1);
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);

    ssd1306_init(i2c1, OLED_ADDR);

    while (true) {

        //Counting
        int reading = gpio_get(BUTTON1);
        if (reading != lastReading) {
            lastChange = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange > DEBOUNCE && reading != buttonState) {
            buttonState = reading;
            // Put Results Here!
            if (buttonState == 0){
            lastConfirmedPress = time_us_64() / 1000;
            }
            else {
                lastConfirmedRelease = time_us_64() / 1000;
                if (lastConfirmedRelease - lastConfirmedPress > morsePause) {
                    morse[morseValue] = 1;
                }
                else {
                    morse[morseValue] = 0;
                }
                morseValue += 1;
            }
        }
        lastReading = reading;

        //Morse to Numbers
        if (morseValue == 5) {
            if (morse[0] == 0 && morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 1;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 0 && morse[1] == 0 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 2;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 0 && morse[1] == 0 && morse[2] == 0 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 3;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 0 && morse[1] == 0 && morse[2] == 0 && morse[3] == 0 && morse[4] == 1) {
                number[numberValue] = 4;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 0 && morse[1] == 0 && morse [2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 5;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 1 && morse[1] == 0 && morse[2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 6;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 1 && morse[1] == 1 && morse[2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 7;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 1 && morse[1] == 1 && morse[2] == 1 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 8;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 1 && morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 0) {
                number[numberValue] = 9;
                numberValue += 1;
                morseValue = 0;
            }
            if (morse[0] == 1 && morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 0;
                numberValue += 1;
                morseValue = 0;
            }
        }

        //Display
        ssd1306_clear();

        if (numberValue > 0) {
            for (int i = 0; i < numberValue; i++) {
                snprintf(text, sizeof(text), "%d", number[i]);
                ssd1306_text(i * 10, 0, text);
            }
        }
        if (morseValue < 5) {
            for (int i = 0; i < morseValue; i++) {
                if (morse[i] == 1) {
                    ssd1306_text(i * 10, 10, "-");
                }
                else {
                    ssd1306_text(i * 10, 10, ".");
                }
            }
        }

        ssd1306_show(i2c1, OLED_ADDR);

    }
}
