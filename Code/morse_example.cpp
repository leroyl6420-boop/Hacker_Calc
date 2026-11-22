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
