#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

string letter2Morse(string msg);

string letter2Morse(string msg){

    // Define the Morse code mapping
    static unordered_map<char, string> morseCode = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}, {' ', "/"}
    };

    // Convert the message to uppercase
    for (char &c : msg) {
        c = toupper(c);
    }
    // Initialize the encoded string
    string encoded = "";
    // Iterate through each character in the message
    for (char c : msg) {
        // Check if the character is in the Morse code mapping
        if (morseCode.find(c) != morseCode.end()) {
            // Append the Morse code to the encoded string
            encoded += morseCode[c] + " ";
        }
    }

    return encoded;
}

int main(){
    // Ask user for the file name
    cout << "Enter file name: ";
    string textScript;
    cin >> textScript;

    // Configure the file path
    fs::path basePath = fs::current_path();
    fs::path wordPath = basePath / "Normal Words" / (textScript + ".txt");

    // Check if the file exists
    if (!fs::exists(wordPath)) {
        cout << "File not found. Please check the file name and try again." << endl;
        return 1;
    }
    // Open the file
    ifstream file(wordPath);
    if (!file.is_open()) {
        cout << "Error opening file: " << wordPath << endl;
        return 1;
    }
    // Read the file content
    string line;
    cout << "==== Start of Message ====\n" << endl;
    while (getline(file, line)) {
        string morseCode = letter2Morse(line);
        cout << morseCode << endl;
    }
    // Close the file
    file.close();
    cout << "\n==== End of Message ====" << endl;
    return 0;
}