#include <iostream>
#include <random>
#include <algorithm>
#include "battle.h"

using namespace std;

// Global Variables
int playerScore = 0;
int computerScore = 0;

// Function where user chooses rock, paper, or scissor
string chooseRole(){
    string role;
    cout << "Rock, Paper or Scissor? ";
    cin >> role;

    transform(role.begin(),role.end(), role.begin(), ::toupper);

    // Check if they chose rock, paper, or scissor
    if (role == "ROCK" || role == "PAPER" || role == "SCISSOR") {
        return role;
    }
    else{
        cout << "Incorrect, input again" << endl;
        return chooseRole();
    } 
}

// Function where a random function chooses between rock, paper, or scissor
string compRole(){
    int compChoose = rand() % 3;
    string role;

    switch (compChoose)
    {
    case 0:
        role = "ROCK";
        break;
    case 1:
        role = "PAPER";
        break;
    case 2:
        role = "SCISSOR";
        break;
    
    default:
        break;
    }
    return role;
}

// Function that checks who wins
int compare(string user, string computer){
    cout << "User: " << user << endl;
    cout << "Computer: " << computer << endl;
    
    if (user == computer){
        cout << "\nTie!" << endl;
        return 0;
    } 
    else if ((user == "ROCK" && computer == "SCISSOR") ||
               (user == "PAPER" && computer == "ROCK") ||
               (user == "SCISSOR" && computer == "PAPER")) {
        cout << "\nUser Wins!" << endl;
        return 1; // User wins
    } 
    else {
        cout << "\nUser Loss!\n" << endl;
        return -1; // Computer wins
    }
}

// Function that takes the scoring and display
string displayScore(int score, string name){
    if (score > 0){
        // give score to player
        playerScore += 1;
    }
    else if (score < 0){
        // give score to computer
        computerScore += 1;
    }

    string scoreMessage = name + " VS Computer\n" + to_string(playerScore) + " - "+ to_string(computerScore);

    return scoreMessage; 
}
