#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include <cstdio>

int main() {
    //Components
    const uint BUTTONBL = 0;
    const uint BUTTONBR = 1;
    const uint BUTTONTL = 3;
    const uint BUTTONTR = 4;
    const uint SWBLB = 5;
    const uint SWBLA = 6;
    const uint SWTLB = 7;
    const uint SWTLA = 10;
    const uint SDA = 8;
    const uint SCL = 9;
    const uint SWTRA = 12;
    const uint SWTRB = 13;
    const uint SWBRA = 14;
    const uint SWBRB = 15;

    const uint8_t OLED_ADDR = 0x3C;

    //Debounce
    const uint DEBOUNCE = 30;
    int lastReading1 = 1;
    int buttonState1 = 1;
    uint64_t lastChange1 = 0;
    int lastReading2 = 1;
    int buttonState2 = 1;
    uint64_t lastChange2 = 0;
    int lastReading3 = 1;
    int buttonState3 = 1;
    uint64_t lastChange3 = 0;
    int lastReading4 = 1;
    int buttonState4 = 1;
    uint64_t lastChange4 = 0;

    //Morse
    uint64_t lastConfirmedPress1 = 0;
    uint64_t lastConfirmedRelease1 = 0;
    uint64_t lastConfirmedPress2 = 0;
    uint64_t lastConfirmedRelease2 = 0;
    int morse[5]; 
    int morsePause = 250;
    int morseValue = 0;

    //Variables
    int operation[10];
    int operationValue = 0;
    int number[10];
    int numberValue = 0;
    char text[20];
    bool displayChange = true;
    int a = gpio_get(SWTLA);
    int b = gpio_get(SWTRA);
    int c = gpio_get(SWBLA);
    int d = gpio_get(SWBRA);
    int lastA = 0;
    int lastB = 0;
    int lastC = 0;
    int lastD = 0;
    bool aChange = false;
    bool bChange = false;
    bool cChange = false;
    bool dChange = false;

    gpio_init(BUTTONBR);
    gpio_init(BUTTONBL);
    gpio_init(BUTTONTL);
    gpio_init(BUTTONTR);
    gpio_init(SWBLB);
    gpio_init(SWBLA);
    gpio_init(SWTLB);
    gpio_init(SWTLA);
    gpio_init(SWTRA);
    gpio_init(SWTRB);
    gpio_init(SWBRA);
    gpio_init(SWBRB);
    
    i2c_init(i2c0, 100000);
    
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);

    gpio_set_dir(BUTTONBL, GPIO_IN);
    gpio_set_dir(BUTTONBR, GPIO_IN);
    gpio_set_dir(BUTTONTL, GPIO_IN);
    gpio_set_dir(BUTTONTR, GPIO_IN);
    gpio_set_dir(SWBLA, GPIO_IN);
    gpio_set_dir(SWBLB, GPIO_IN);
    gpio_set_dir(SWTLA, GPIO_IN);
    gpio_set_dir(SWTLB, GPIO_IN);
    gpio_set_dir(SWTRA, GPIO_IN);
    gpio_set_dir(SWTRB, GPIO_IN);
    gpio_set_dir(SWBRA, GPIO_IN);
    gpio_set_dir(SWBRB, GPIO_IN);

    gpio_pull_up(BUTTONTL);
    gpio_pull_up(BUTTONTR);
    gpio_pull_up(BUTTONBL);
    gpio_pull_up(BUTTONBR);
    gpio_pull_up(SWTLA);
    gpio_pull_up(SWTLB);
    gpio_pull_up(SWTRA);
    gpio_pull_up(SWTRB);
    gpio_pull_up(SWBLA);
    gpio_pull_up(SWBLB);
    gpio_pull_up(SWBRA);
    gpio_pull_up(SWBRB);
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);

    ssd1306_init(i2c0, OLED_ADDR);

    while (true) {

        //Switch Inputs
        a = gpio_get(SWTLA);
        if (lastA != a) {
            aChange = true;
            bChange = false;
            cChange = false;
            dChange = false;
            if (a == 0) {
                a = 0;
            }
            else {
                a = 1;
            }
        }
        lastA = a;

        b = gpio_get(SWTRA);
        if (lastB != b) {
            bChange = true;
            aChange = false;
            cChange = false;
            dChange = false;
            if (b == 0) {
                b = 0;
            }
            else {
                b = 1;
            }
        }
        lastB = b;

        c = gpio_get(SWBLA);
        if (lastC != c) {
            cChange = true;
            aChange = false;
            bChange = false;
            dChange = false;
            if (c == 0) {
                c = 0;
            }
            else {
                c = 1;
            }
        }
        lastC = c;

        d = gpio_get(SWBRA);
        if (lastD != d) {
            dChange = true;
            aChange = false;
            cChange = false;
            bChange = false;
            if (d == 0) {
                d = 0;
            }
            else{ 
                d = 1;
            }
        }
        lastD = d;

        // Button Inputs
        
        int reading1 = gpio_get(BUTTONTL);
        if (reading1 != lastReading1) {
            lastChange1 = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange1 > DEBOUNCE && reading1 != buttonState1) {
            buttonState1 = reading1;
            if (buttonState1 == 0) {
                lastConfirmedPress1 = time_us_64() / 1000;
            }
            if (buttonState1 == 1 && morseValue < 5) {
                lastConfirmedRelease1 = time_us_64() / 1000;
                if (lastConfirmedRelease1 - lastConfirmedPress1 > morsePause) {
                    morse[morseValue] = 1;
                }
                else {
                    morse[morseValue] = 0;
                }
                morseValue += 1;
                displayChange = true;
            }
        }
        lastReading1 = reading1;

        int reading2 = gpio_get(BUTTONTR);
        if (reading2 != lastReading2) {
            lastChange2 = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange2 > DEBOUNCE && reading2 != buttonState2) {
            buttonState2 = reading2;
            if (buttonState2 == 0) {
                if (aChange == true) {
                    if (a == 0) {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 1;
                        operationValue += 1;
                        displayChange = true;
                    }
                    else {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 2;
                        operationValue += 1;
                        displayChange = true;
                    }
                }
                if (bChange == true) {
                    if (b == 0) {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 3;
                        operationValue += 1;
                        displayChange = true;
                    }
                    else {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 4;
                        operationValue += 1;
                        displayChange = true;
                    }
                }
                if (cChange == true) {
                    if (c == 0) {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 5;
                        operationValue += 1;
                        displayChange = true;
                    }
                    else {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 6;
                        operationValue += 1;
                        displayChange = true;
                    }
                }
                if (dChange == true) {
                    if (d == 0) {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 7;
                        operationValue += 1;
                        displayChange = true;
                    }
                    else {
                        number[numberValue] = 10;
                        numberValue += 1;
                        operation[operationValue] = 8;
                        operationValue += 1;
                        displayChange = true;
                    }
                }
            }
        }
        lastReading2 = reading2;

        int reading3 = gpio_get(BUTTONBL);
        if (reading3 != lastReading3) {
            lastChange3 = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange3 > DEBOUNCE && reading3 != buttonState3) {
            buttonState3 = reading3;
            // Put Results Here!
        }
        lastReading3 = reading3;

        int reading4 = gpio_get(BUTTONBR);
        if (reading4 != lastReading4) {
            lastChange4 = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange4 > DEBOUNCE && reading4 != buttonState4) {
            buttonState4 = reading4;
            if (buttonState4 == 0) {
                lastConfirmedPress2 = time_us_64() / 1000;
            }
            if (buttonState4 == 1) {
                lastConfirmedRelease2 = time_us_64() / 1000;
                if (lastConfirmedRelease2 - lastConfirmedPress2 > morsePause) {
                    morseValue = 0;
                    numberValue = 0;
                    operationValue = 0;
                    displayChange = true;
                }
                else {
                    morseValue = 0;
                    displayChange = true;
                }
            }
        } 
        lastReading4 = reading4;

        //Morse to Numbers

        if (morseValue == 5) {
            if (morse[0] == 0 && morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 1;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 0 && morse[1] == 0 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 2;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 0 && morse[1] == 0 && morse[2] == 0 && morse[3] == 1 && morse[4] == 1) {
                number[numberValue] = 3;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 0 && morse[1] == 0 && morse[2] == 0 && morse[3] == 0 && morse[4] == 1) {
                number[numberValue] = 4;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 0 && morse[1] == 0 && morse[2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 5;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 1 && morse[1] == 0 && morse[2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 6;     
                numberValue += 1;
                morseValue = 0;      
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 1 && morse[1] == 1 && morse[2] == 0 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 7;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 1 && morse[1] == 1 && morse[2] == 1 && morse[3] == 0 && morse[4] == 0) {
                number[numberValue] = 8;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[0] == 1 && morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 0) {
                number[numberValue] = 9;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else if (morse[1] == 1 && morse[2] == 1 && morse[3] == 1 && morse[4] == 1 && morse[0] == 1) {
                number[numberValue] = 0;
                numberValue += 1;
                morseValue = 0;
                displayChange = true;
                operation[operationValue] = 0;
                operationValue += 1;
            }
            else {
                morseValue = 0;
                displayChange = true;
            }
        }

        //Computation

        //Display

        if (displayChange == true) {
            ssd1306_clear();

            //Number/Operation Display

            for (int i = 0; i < numberValue; i++) {
                if (number[i] != 10) {
                    snprintf(text, sizeof(text), "%d", number[i]);
                    ssd1306_text(i * 10, 0, text);
                }
                else {
                    if (operation[i] == 1) {
                        ssd1306_text(i * 10, 0, "TLA");
                    }
                    if (operation[i] == 2) {
                        ssd1306_text(i * 10, 0, "TLB");
                    }
                    if (operation[i] == 3) {
                        ssd1306_text(i * 10, 0, "TRA");
                    }
                    if (operation[i] == 4) {
                        ssd1306_text(i * 10, 0, "TRB");
                    }
                    if (operation[i] == 5) {
                        ssd1306_text(i * 10, 0, "BLA");
                    }
                    if (operation[i] == 6) {
                        ssd1306_text(i * 10, 0, "BLB");
                    }
                    else {
                        //Add move on and execute signals here!
                    }
                }
            }

            //Morse Display

            for (int i = 0; i < morseValue; i++) {
                if (morse[i] == 1) {
                    ssd1306_text(i * 10, 50, "-");
                }
                if (morse[i] == 0) {
                    ssd1306_text(i * 10, 50, ".");
                }
            }

            ssd1306_show(i2c0, OLED_ADDR);
        }

        displayChange = false;

    }
}
