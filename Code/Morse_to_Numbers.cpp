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
