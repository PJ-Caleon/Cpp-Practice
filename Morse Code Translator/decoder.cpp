#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

// Functions used
void msgWordSplit(string msg);
void msgLetterSplit(string word);
void msgDecoder(string letter);
char cheatSheet(string letter);

void msgWordSplit(string msg){ 
    // Split string to word
    // Step 1: Count how many times '/' appears in string
    int space = 0;
    for (int i = 0; i < msg.length(); i++){
        if (msg[i] == '/'){
            space += 1;
        }
    }
    string words[space];

    // Step 2: Split string into words
    int j = 0;
    for (int i = 0; i < msg.length(); i++){
        // If '/' is found, split the string
        if (msg[i] == '/'){
            // Store the word in the array
            // and erase the word from the string
            words[j] = msg.substr(0, i);
            msg.erase(0, i + 1);
            j += 1;
            i = 0;
        }
    }
    words[j] = msg.substr(0, msg.length());

    // Step 3: Send each word to msgLetterSplit
    for (int i = 0; i < space + 1; i++){
        msgLetterSplit(words[i]);
    }
}

void msgLetterSplit(string word){
    // Step 1: Count how many times ' ' appears in string
    int space = 0;
    for (int i = 0; i < word.length(); i++){
        if (word[i] == ' '){
            space += 1;
        }
    }
    string letters[space+1];

    // Step 2: Split string into letters
    int j = 0;
    for (int i = 0; i < word.length(); i++){
        // If ' ' is found, split the string
        if (word[i] == ' '){
            // Store the letter in the array
            // and erase the letter from the string
            letters[j] = word.substr(0, i);
            word.erase(0, i + 1);
            j += 1;
            i = 0;
        }
    }
    letters[j] = word.substr(0, word.length());

    // Step 3: Send to decoder
    for (int i = 0; i < space + 1; i++){
        msgDecoder(letters[i]);
    }
}

void msgDecoder(string letter){
    char decodedLetter = cheatSheet(letter);
    cout << decodedLetter;
}

char cheatSheet(string letter){
    // Define the Morse code to character mapping
    static unordered_map<string, char> morseToChar = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
        {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
        {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
        {"--..", 'Z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'},
        {"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'},
        {"--...", '7'}, {"---..", '8'}, {"----.", '9'}
    };

    // Look up the letter in the map
    if (morseToChar.find(letter) != morseToChar.end()) {
        return morseToChar[letter];
    } else {
        return ' '; // Assume space for invalid Morse code
    }
}

int main(){
    string textScript;

    // Ask user to input txt file
    cout << "Enter file name: ";
    cin >> textScript;

    // Configure the file path
    fs::path basePath = fs::current_path();
    fs::path morseCodePath = basePath / "Morse Codes" / (textScript + ".txt");

    // Open the file
    ifstream file(morseCodePath);

    if (!file.is_open()) {
        cout << "Error opening file: " << morseCodePath << endl;
        return 1;
    }

    // Read the file content
    string line;
    while (getline(file, line)) {
        cout << "==== Start of message ====\n" << endl;
        // Send to Decoder functions
        msgWordSplit(line);
        cout << "\n\n==== End of Message ====" << endl;
    }

    // Close the file
    file.close();

    return 0;
}
