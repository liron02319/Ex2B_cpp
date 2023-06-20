#ifndef CARD_H
#define CARD_H

/**
 * Header file of class "Card"
 */

#include <iostream>
using namespace std;


namespace ariel{

class Card 
{
    
private: 

    int number; //declaration of variables
    string shape;
    
public:

    //constructors
    Card(int number, string shape); // "outline" constructor

    //GET Functions 
    int getNumber();
    string getShape();

    //SET Functions 
    void setNumber(int number);
    void setShape(string shape);

    void toString();
        
        
};

//ENUM
enum CardValue {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK = 11,
    QUEEN = 12,
    KING = 13
};

}











#endif