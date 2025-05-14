#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <atomic>
#include <algorithm>

using namespace std;

// Global Variables
bool isActive = false;
bool timerActive = false;
int totalScore = 0;

// Timer Variable - This can be changed to set the time
int gameTime = 15;
// Timer Variable - This can be changed to set the time

const int BEFORE_TIME = gameTime;
std::atomic<int> timer(gameTime); 

// Functions used
bool isGameActive(char input);
void preGame();
int game();
string getRandomWord();
string userInput();
void timerCountdown();
int checker(string word, string input);

int pointAdder(int score){
    // Function that adds points to the score if correct
    totalScore += score;
    return totalScore;
}

int checker(string word, string input){
    int point = 0;
    // Convert both strings to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    // Function that checks if the word is correct
    if (word == input) {
        point += 1;
    } 
    return point;
}

string userInput(){
    string input;
    cout << "Enter the word: ";
    cin >> input;
    return input;
}

void timerCountdown(){
    // Every second, timer will decrease by 1
    while (timer > 0 && timerActive) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        timer--;
    }
    timerActive = false;
}

// Function to get a random word from a txt file
string getRandomWord() {
    // Opening wordBank.txt file
    ifstream file("wordBank.txt");
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return "";
    }
    // Read all words into a vector
    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    // Generate a random index
    random_device rd;
    mt19937 gen(rd()); // This is Mersene Twister random number generator 
    uniform_int_distribution<> dis(0, words.size() - 1);
    int randomIndex = dis(gen);

    // Return the random word
    return words[randomIndex];
}

// Main function that runs the game
int game() {

    // Function that sets the time loop of how many points the user can get
    timerActive = true;
    thread timerThread(timerCountdown);

    while (timerActive) {
        // Function that gets a random word from a txt file
        string word = getRandomWord();
        cout << "Type the word: " << word << endl;
        
        // Function that gets word from user
        string input = userInput();

        // Function that checks if the word is correct
        int score = checker(word, input);

        // Function that adds points to the score if correct
        pointAdder(score);

        system("clear");
    }
    if (timerThread.joinable()) {
        timerThread.join();
    }

    return totalScore;
}

// Function that tells instructions to the user and Ask if player is ready
void preGame(){
    int score;

    cout << "Instructions: \nType the words as fast as you can!\nThere is a " << BEFORE_TIME << " second timer\nEnter as many correct words to gain points!\n\n (This is not case sensitive)" << endl;

    cout << "\nAre you Ready?\nPress 'z' to start the game.\n>";
    char input;
    cin >> input;
    system("clear");

    if (input == 'z'){
        // Send user to game function
        score = game();
    }
    // Computes words per second
    double wps = static_cast<double>(score) / BEFORE_TIME;

    cout << "Game Over!\n" << endl;
    cout << "Your score is: " << score << endl;
    cout << fixed << setprecision(2) << wps << " wps (Words Per Second)\n" << endl;
}

// Function to check if the game is active
bool isGameActive(char input) {
    
    if (input == 'z') {
        isActive = true;
        gameTime = BEFORE_TIME;
        timer = gameTime; // Reset the timer
        timerActive = false; // Reset the timerActive flag
        totalScore = 0; // Reset the score
        system("clear");
    } else if (input == 'x') {
        isActive = false;
    } else {
        cout << "Invalid input. Please press 'z' to start or 'x' to quit." << endl;
    }
    
    return isActive;
}

int main(){
    // Game Loop
    cout << "Welcome to the Typing Game!" << endl;
    cout << "Press 'z' to start the game." << endl;
    cout << "Press 'x' to quit the game.\n>";
    char input;
    cin >> input;

    system("clear");
    isGameActive(input);
    
    while (isActive){
        // Move to Game function
        preGame();
        

        // Restart the game
        cout << "Press 'z' to Restart" << endl;
        cout << "Press 'x' to quit the game.\n>";
        cin >> input;

        system("clear");
        isGameActive(input);
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}