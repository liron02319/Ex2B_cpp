/**
 * Implementation file of class "Player"
 */
#include "player.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ariel;


// "outline" constructor implementation:
Player :: Player(string name){
    
    this ->name = name;
    this ->numberOfCardsIWon = 0;
    this ->countWins = 0;
}


 //*** GET Functions ***
string Player :: getName(){
    return this -> name;
}

int Player :: getNumberOfCardsIWon(){
    return this -> numberOfCardsIWon;
}

int Player :: getCountWins(){
    return this ->countWins;
}

 //*** SET Functions ***

void Player :: setNumberOfCardsIWon(int numberOfCardsIWon){
    this -> numberOfCardsIWon = numberOfCardsIWon;
}

void Player :: setCountWins(int countWins){
    this -> countWins = countWins;
}


//stack

bool Player :: emptyStack(){
    return this-> stackOfPlayer.empty();
}

void Player :: popStack(){
    this->stackOfPlayer.pop();
}

Card Player :: topStack(){
    return this ->stackOfPlayer.top();
}

void Player :: pushToStack(Card card){
    this ->stackOfPlayer.push(card);
}


 //Functions requested for implementation
int Player :: stacksize(){
    return this -> stackOfPlayer.size();
}


int Player :: cardesTaken(){
    return this -> numberOfCardsIWon;
}


