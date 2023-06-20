/**
 * Implementation file of class "Card"
 */

#include <iostream>
#include "card.hpp"
using namespace ariel;


// "outline" constructor implementation:
Card :: Card (int number, string shape){

    this ->number = number;
    this ->shape = shape;
}

 //*** GET Functions ***
int Card :: getNumber(){
    return this ->number;
}

string Card :: getShape(){
    return this -> shape;
}

 //*** SET Functions ***
void Card :: setNumber(int number){
    this -> number = number;
}

void Card :: setShape(string shape){
    this -> shape = shape;
}

void Card :: toString (){
    cout <<  "Number: " <<  this->number << " Shape: " << this->shape << endl;
}



