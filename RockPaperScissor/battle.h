#ifndef BATTLE_H
#define BATTLE_H

#include <string> 
using namespace std;

// Declare the functions from battle.cpp
string chooseRole();
string compRole();
int compare(string user, string computer);
string displayScore(int score, string name);

#endif // BATTLE_H