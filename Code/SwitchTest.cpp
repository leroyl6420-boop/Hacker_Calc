#include "pico/stdlib.h"

int main() {
    //Components
    const uint BUTTON = 0;
    const uint SW1 = 1;
    const uint SW2 = 2;
    const uint SW3 = 3;
    const uint SW4 = 4;
    const uint LED = 5;

    bool S1 = false;
    bool S2 = false;
    bool S3 = false;
    bool S4 = false;

    gpio_init(BUTTON);
    gpio_init(LED);
    gpio_init(SW1);
    gpio_init(SW2);
    gpio_init(SW3);
    gpio_init(SW4);

    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_set_dir(SW1, GPIO_IN);
    gpio_set_dir(SW2, GPIO_IN);
    gpio_set_dir(SW3, GPIO_IN);
    gpio_set_dir(SW4, GPIO_IN);

    gpio_pull_up(BUTTON);
    gpio_pull_up(SW1);
    gpio_pull_up(SW2);
    gpio_pull_up(SW3);
    gpio_pull_up(SW4);

    while (true) {
        //Read Switch States
        if (gpio_get(SW1) == 0) {
            S1 = true;
        }
        else {
            S1 = false;
        }
        if (gpio_get(SW2) == 0) {
            S2 = true;
        }
        else {
            S2 = false;
        }
        if (gpio_get(SW3) == 0) {
            S3 = true;
        }
        else {
            S3 = false;
        }
        if (gpio_get(SW4) == 0) {
            S4 = true;
        }
        else {
            S4 = false;
        }
        
        //Display Switch States
        if (gpio_get(BUTTON) == 0){
            if (S1 == true) {
                gpio_put(LED, 1);
                sleep_ms(1000);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S1 == false) {
                gpio_put(LED, 1);
                sleep_ms(200);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S2 == true) {
                gpio_put(LED, 1);
                sleep_ms(1000);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S2 == false) {
                gpio_put(LED, 1);
                sleep_ms(200);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S3 == true) {
                gpio_put(LED, 1);
                sleep_ms(1000);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S3 == false) {
                gpio_put(LED, 1);
                sleep_ms(200);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S4 == true) {
                gpio_put(LED, 1);
                sleep_ms(1000);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
            if (S4 == false) {
                gpio_put(LED, 1);
                sleep_ms(200);
                gpio_put(LED, 0);
                sleep_ms(200);
            }
        }
    }

}
