if (morseToChar.find(letter) != morseToChar.end()) {
        return morseToChar[letter];
    } else {
        return ' '; // Assume space for invalid Morse code
    }