#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

int main() {
    //Components
    const uint BUTTON1 = 0;
    const uint SDA = 6;
    const uint SCL = 7;

    //Debounce
    const uint DEBOUNCE = 50;
    int lastReading = 1;
    int buttonState = 1;
    uint64_t lastChange = 0;
    uint64_t lastConfirmedPress = 0;
    uint64_t lastConfirmedRelease = 0;

    //Variables
    bool pressed = false;

    i2c_init(i2c1, 400000);
    gpio_init(BUTTON1);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);

    gpio_set_dir(BUTTON1, GPIO_IN);

    gpio_pull_up(BUTTON1);
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);

    ssd1306_t oled;

    ssd1306_init(
        &oled,
        128,
        64,
        0x3D,
        i2c1
    );

    while (true) {

        if (pressed == true) {
            ssd1306_clear(&oled);

            ssd1306_draw_string(&oled, 0, 0, 1, "1");

            ssd1306_show(&oled);
        }
        else{
            ssd1306_clear(&oled);
        
            ssd1306_draw_string(&oled, 0, 0, 1, "0");

            ssd1306_show(&oled);
        }

        //Counting
        int reading = gpio_get(BUTTON1);
        if (reading != lastReading) {
            lastChange = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange > DEBOUNCE && reading != buttonState) {
            buttonState = reading;
            // Put Results Here!
            if (buttonState == 0){
            pressed = true;
            }
            else {
                pressed = false;
            }
        }
        lastReading = reading;



    }
}
