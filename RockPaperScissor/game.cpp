// Started May 14, 2025

#include <iostream>
#include <cstdlib>
#include "battle.h"

using namespace std;

// Global Variables
bool isActive = false;

// Functions used
bool restart(char opt);

bool restart(char opt){
    switch (opt)
    {
    case 'Y':
        isActive = true;
        break;
    case 'y':
        isActive = true;
        break;
    default:
        isActive = false;
        break;
    }
    return isActive;
}

int main(){
    cout << "Welcome User! \nEnter your name: ";
    string name;
    cin >> name;

    cout << "Welcome again " << name << " to Rock Paper Sciccors" << endl;
    cout << "Would you like to play? [Y/n] ";
    char opt;
    cin >> opt;

    isActive = restart(opt);

    while(isActive){
        // Send to battle.cpp
        system("clear");
        string userRole, computerRole;
        int score;

        // Ask users role
        userRole = chooseRole();

        // Ask random functions role
        computerRole = compRole();

        // Checks who wins
        score = compare(userRole, computerRole);

        // Display Score
        cout << displayScore(score, name) << endl;

        cout << "\nWould you like to play again? [Y/n] ";
        cin >> opt;
        isActive = restart(opt);
    }

    cout << "Thank you for Playing!" << endl;
}

// To compile
// g++ game.cpp battle.cpp -o game

// To Run
// ./game