int reading = gpio_get(BUTTON1);
        if (reading != lastReading) {
            lastChange = time_us_64() / 1000;
        }
        if (time_us_64() / 1000 - lastChange > DEBOUNCE && reading != buttonState) {
            buttonState = reading;
            // Put Results Here!
            
        }
        lastReading = reading;
