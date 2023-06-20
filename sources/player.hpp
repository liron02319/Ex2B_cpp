#ifndef PLAYER_H
#define PLAYER_H

/**
 * Header file of class "Player"
 */

#include <iostream>
#include <string>
#include <stack>
#include "card.hpp"
using namespace std;

namespace ariel {

class Player
{

private: 

    string name;
    int numberOfCardsIWon;
    int countWins;
    stack <Card> stackOfPlayer; 



public:

    //constructor
    Player(string name);   // "outline" constructor


    //*** GET Functions ***
    string getName();
    int getNumberOfCardsIWon();
    int getCountWins();

     //*** SET Functions ***
    void setName(string name);
    void setNumberOfCardsIWon(int numberOfCardsIWon);
    void setCountWins(int countwins);


    //Help functions for stack
    bool emptyStack();
    void popStack();
    Card topStack();
    void pushToStack(Card card);

    //Functions requested for implementation
    int stacksize();  //prints the amount of cards left to the player
    int cardesTaken();  /// prints the amount of cards this player has won. 
 

};

}
#endif
