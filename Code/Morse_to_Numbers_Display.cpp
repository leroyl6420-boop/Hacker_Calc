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
