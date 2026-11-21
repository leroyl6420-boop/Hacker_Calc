#include "pico/stdlib.h"

int main() {
    //Components
    const uint BUTTON1 = 0;
    const uint BUTTON2 = 1;
    const uint LED = 8;
    
    //Debounce

    const uint DEBOUNCE = 50;
    int lastReading = 1;
    int buttonState = 1;
    uint64_t lastChange = 0;
    uint64_t lastConfirmedPress = 0;
    uint64_t lastConfirmedRelease = 0;

    //Variables

    int morse[10];
    int morseLength = 0;
    const int morseValue = 500;

    gpio_init(BUTTON1);
    gpio_init(LED);
    gpio_init(BUTTON2);

    gpio_set_dir(BUTTON1, GPIO_IN);
    gpio_set_dir(BUTTON2, GPIO_IN);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_pull_up(BUTTON1);
    gpio_pull_up(BUTTON2);

    while (true) {

        //Counting
        int reading = gpio_get(BUTTON1);
        if (reading != lastReading) {
            lastChange = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange > DEBOUNCE && reading != buttonState) {
            buttonState = reading;
            // Put Results Here!
            if (buttonState == 0) {
                lastConfirmedPress = time_us_64() / 1000;
            }
            if (buttonState == 1) {
                lastConfirmedRelease = time_us_64() / 1000;
                if (lastConfirmedRelease - lastConfirmedPress < morseValue) {
                morse[morseLength] = 0;
                morseLength += 1;
                }
                else {
                    morse[morseLength] = 1;
                    morseLength += 1;
                }
            }
        }
        lastReading = reading;

        //Displaying Count
        if (gpio_get(BUTTON2) == 0) {
            for (int i = 0; i < morseLength; i++) {
                if (morse[i] == 1){
                    gpio_put(LED, 1);
                    sleep_ms(1000);
                    gpio_put(LED, 0);
                    sleep_ms(200);
                }
                else {
                    gpio_put(LED, 1);
                    sleep_ms(200);
                    gpio_put(LED, 0);
                    sleep_ms(200);
                }
            }
            morseLength = 0;
        }

    }
}
