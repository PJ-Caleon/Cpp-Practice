#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

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
        cout << line << endl;
    }
    // Close the file
    file.close();
    cout << "\n==== End of Message ====" << endl;
    return 0;
}