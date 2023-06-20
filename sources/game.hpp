#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "player.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include "card.hpp"

/**
 * Header file of class "Game"
 */
using namespace std;

namespace ariel{

class Game {


private:

    Player &player1;
    Player &player2;

    vector <Card> stackOfTheGame; // would contain 52 cards
    vector <string> logOfGame; // save happens in each round
    vector <Card> tableCards; // cards that we put on table

    int countDraws;
    bool gameOver; 



public:

    //constructors
    Game(Player &player1, Player &player2);  // "outline" constructor
    

    //Functions of the game - Functions requested for implementation
    void playTurn();
    void printLastTurn(); //print the last turn stats
    void playAll(); //playes the game untill the end
    void printWiner(); // prints the name of the winning player
    void printLog(); // prints all the turns played one line per turn
    void printStats(); //for each player prints basic statistics(etc - cards player won)

    string toString();
    
    void clearTable(); //help function

    string getCardValueName(int value); //help function for enum


};
}

#endif