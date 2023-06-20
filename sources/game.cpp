#include <iostream>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <thread>
#include <chrono>

using namespace ariel;
using namespace std;



/*
    Details of The Game:

    Every game is played with 2 players. 
    Every player start the game with 26 cards. 

    ** only one round is played. 

    At each turn, the players put down the first card on the top of the deck, 
    and the player the has the bigger card - takes 2 cards(his card +his enemy player). 
    **Ace beats all of the cardes except "2".
    
    If their is a draw, each player puts down 2 cards, one downwards, and then one 
    upwards. The player who wins - takes all of the card to him.
    **if the last turn ends with a draw, every player take back the cardes he put on table.

    The winner is the player that has the most cards at the end of the game. 

*/



//divide the cards to 2 players
void divideTheCards(Player &player1, Player &player2, vector <Card> &stackOfTheGame){
    for (size_t i = 0; i < 52; i++) {
        if (i % 2 == 0)
            player1.pushToStack(stackOfTheGame[i]);
        else
            player2.pushToStack(stackOfTheGame[i]);
    }

}

//initiaize the stack
void initializeStack(vector <Card> &stackOfTheGame) { // 52 cards in stack and,4 shapes,13 types,
    for (int i = 0; i < 13; i++) {
        stackOfTheGame.push_back(Card(i+1, "Clubs"));
        stackOfTheGame.push_back(Card(i+1, "Hearts"));
        stackOfTheGame.push_back(Card(i+1, "Diamonds"));        
        stackOfTheGame.push_back(Card(i+1, "Spades"));

    }
}


// "outline" constructor implementation:

Game :: Game (Player &player1, Player &player2)  : player1(player1), player2(player2){

    //if player name empty
    if (this -> player1.getName().empty() || this -> player2.getName().empty()){
        throw std :: invalid_argument ("Invalid Argument Name,Please check the names argument ");
    }

    initializeStack(this -> stackOfTheGame); // initialize Stack : 52 cards in stack and,4 shapes,13 types,

    if (stackOfTheGame.size() != 52) {
        throw std :: invalid_argument ("The stack is More Or Less then 52 cards, Please restart the game \n");
    }

    random_device randomForStack; //Create a random device to generate a seed value for the random number generator

    mt19937 g(randomForStack()); //Create a Mersenne Twister random number generator with the seed value from the random device


    shuffle(stackOfTheGame.begin(), stackOfTheGame.end(), g); // Shuffle the vector using the random number generator

    if (stackOfTheGame.size() != 52) {
        throw std :: invalid_argument ("The stack is More Or Less then 52 cards, Please restart the game \n");
    }

    divideTheCards(this ->player1, this ->player2, stackOfTheGame); //divide cards to players

    // Initializing 
    this -> player1.setCountWins(0);
    this -> player2.setCountWins(0);
    this -> countDraws = 0;
    this -> gameOver = false;
    

}


/*
###playTurn Function
play 1 turn
*/

void Game :: playTurn(){

 // Make sure game is valid before playing :

    if (gameOver){
        throw logic_error ("Game is over, please restart the game.");
        return;
    }

    if(&player1==&player2){        
    throw ("same player can not play againt himself.");
    }

    if(player1.stacksize() == 0 || player2.stacksize() == 0){ //the amount of cards that have to the player
        gameOver = true;
        printLastTurn();
        return;
    }

    Card cardOfPlayer1 = player1.topStack(); //get the details of card
    Card cardOfPlayer2 = player2.topStack(); //get the details of card
    player1.popStack(); //remove from the stack of the player
    player2.popStack(); //remove from the stack of the player

    string shapeOfCardPlayer1 = cardOfPlayer1.getShape();
    string shapeOfCardPlayer2 = cardOfPlayer2.getShape();
    string numberOfCardPlayer1 = getCardValueName(cardOfPlayer1.getNumber()) + " of ";
    string numberOfCardPlayer2 = getCardValueName(cardOfPlayer2.getNumber()) + " of ";
    string winner = " ";

    string toPush = this -> player1.getName() + " played "+ numberOfCardPlayer1 + shapeOfCardPlayer1 + " and " + this ->player2.getName() + " played " + numberOfCardPlayer2 + shapeOfCardPlayer2 + ", ";

    // Ace wins all but not 2
    if (cardOfPlayer1.getNumber() == 1 && cardOfPlayer2.getNumber() != 2 && cardOfPlayer1.getNumber() !=cardOfPlayer2.getNumber()){
        player1.setCountWins(player1.getCountWins()+1);
        // player1 which is the winner takes both cards
        player1.setNumberOfCardsIWon(player1.getNumberOfCardsIWon() + 2);
        winner = this->player1.getName() + " wins!";
        toPush=toPush+winner;
        this->logOfGame.push_back(toPush);
            
    }

    // Ace wins all but not 2
    else if (cardOfPlayer1.getNumber() != 2 && cardOfPlayer2.getNumber() == 1 && cardOfPlayer1.getNumber() !=cardOfPlayer2.getNumber()){
        player2.setCountWins(player2.getCountWins()+1);
        player2.setNumberOfCardsIWon(player2.getNumberOfCardsIWon() + 2); // player2 which is the winner takes both cards
        winner = this->player2.getName() + " wins!";
        toPush=toPush+winner;
        this->logOfGame.push_back(toPush);
    }

    // Else if player1 wins the round:
    else if (cardOfPlayer1.getNumber() > cardOfPlayer2.getNumber()){
        player1.setCountWins(player1.getCountWins()+1);
        player1.setNumberOfCardsIWon(player1.getNumberOfCardsIWon() + 2);         // player1 which is the winner takes both cards
        winner = this->player1.getName() + " wins!";
        toPush=toPush+winner;
        this->logOfGame.push_back(toPush);
    }

    // If player2 wins the round:
    else if (cardOfPlayer1.getNumber() < cardOfPlayer2.getNumber()){
        player2.setCountWins(player2.getCountWins()+1);
        player2.setNumberOfCardsIWon(player2.getNumberOfCardsIWon() + 2);         // player2 which is the winner takes both cards
        winner = this->player2.getName() + " wins!";
        toPush=toPush+winner;
        this->logOfGame.push_back(toPush);
    }
     else {
        winner =  " Draw!";
        //***DRAW***;

        vector <Card> tableCards; // cards that we put on table
        while (cardOfPlayer1.getNumber() == cardOfPlayer2.getNumber())
        {

            this ->countDraws++;

            // if can not do the war
            if (this -> player1.stacksize() <2 && this -> player2.stacksize() < 2 ){
                    
                player1.setNumberOfCardsIWon(player1.getNumberOfCardsIWon() + player1.stacksize()+1);
                player2.setNumberOfCardsIWon(player2.getNumberOfCardsIWon() + player1.stacksize()+1);
                if (!player1.emptyStack()) {
                    player1.popStack();
                }
                if (!player2.emptyStack()) {
                    player2.popStack();
                }
                gameOver = true; 
                break;
            }

            // else start the war:
            tableCards.push_back(cardOfPlayer1); //add the draw player1 card to tableCards
            tableCards.push_back(cardOfPlayer2); //add the draw player2 card to tableCards

            cardOfPlayer1 = this -> player1.topStack(); //take info of card
            cardOfPlayer2 = this -> player2.topStack(); //take info of card
            tableCards.push_back(cardOfPlayer1); // the upside down card(add player1 card to tableCards)
            tableCards.push_back(cardOfPlayer2); // the upside down card(add player2 card to tableCards)

            this -> player1.popStack(); //remove upside card from stack of player1 
            this -> player2.popStack(); //remove upside card from stack of player2 

            cardOfPlayer1 = this -> player1.topStack();//take info of card
            cardOfPlayer2 = this -> player2.topStack(); //take info of card

            this -> player1.popStack(); //remove third card from stack of player1 
            this -> player2.popStack(); //remove third card from stack of player2 

            tableCards.push_back(cardOfPlayer1); //add the current card(the third) to tableCards
            tableCards.push_back(cardOfPlayer2); //add the current card(the third) to tableCards



            // Ace(1) wins all but not 2
            if (cardOfPlayer1.getNumber() == 1 && cardOfPlayer2.getNumber() != 2 &&cardOfPlayer2.getNumber()!=1)  {
                player1.setCountWins(player1.getCountWins()+1);
                // player1 which is the winner takes both cards
                int toAdd = tableCards.size();
                player1.setNumberOfCardsIWon(player1.getNumberOfCardsIWon() + toAdd);
                clearTable();                
            }

                // Ace(1) wins all but not 2
                else if (cardOfPlayer1.getNumber() != 2 && cardOfPlayer2.getNumber() == 1 &&cardOfPlayer1.getNumber()!=1){
                    player2.setCountWins(player2.getCountWins()+1);
                    // player2 which is the winner takes both cards
                    int toAdd = tableCards.size();
                    player2.setNumberOfCardsIWon(player2.getNumberOfCardsIWon() + toAdd);
                    clearTable();   
                }

                // Else if player1 wins the round
                else if (cardOfPlayer1.getNumber() > cardOfPlayer2.getNumber() && cardOfPlayer2.getNumber() != 1){
                    player1.setCountWins(player1.getCountWins()+1);
                    // player1 which is the winner takes both cards
                    int toAdd = tableCards.size();
                    player1.setNumberOfCardsIWon(player1.getNumberOfCardsIWon() + toAdd);
                    clearTable();   
                }

                // Else if player2 wins the round
                else if (cardOfPlayer1.getNumber() < cardOfPlayer2.getNumber() && cardOfPlayer1.getNumber() != 1){
                    player2.setCountWins(player2.getCountWins()+1);
                    // player2 which is the winner takes both cards
                    int toAdd = tableCards.size();
                    player2.setNumberOfCardsIWon(player2.getNumberOfCardsIWon() + toAdd);
                    clearTable();   
                }


            }

            //after the war checks
            if (player1.stacksize() == 0 && player2.stacksize() == 0)
            {
            gameOver = true;
            if (player1.getNumberOfCardsIWon() > player2.getNumberOfCardsIWon()){
                cout << player1.getNumberOfCardsIWon() << " " << player2.getNumberOfCardsIWon() << endl;
                cout << player1.getName() << " won!" << endl;
            }
            else if (player1.getNumberOfCardsIWon() < player2.getNumberOfCardsIWon()){
                cout << player1.getNumberOfCardsIWon() << " " << player2.getNumberOfCardsIWon() << endl;
                cout << player2.getName() << " won!" << endl;
            }
            else{
                cout << player1.getNumberOfCardsIWon() << " " << player2.getNumberOfCardsIWon() << endl;
                cout << " Game ended with a tie(both players have the same count of cards at stack)" << endl;
            }
            }
        

    }
    
}

//help function
//clean the cards that we put on table because of draw
void Game :: clearTable(){

    while (!tableCards.empty()){
     tableCards.pop_back();
    }

}


/*
###printLastTurn Function
// print the last turn stats. For example:
// Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
// Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
*/
void Game :: printLastTurn(){

   if (logOfGame.empty()){
        throw std::runtime_error("the log Of Game is empty, can't print the last turn");
        return;
    }
    string lastTurn = "";
    lastTurn = logOfGame.back();  
    cout << lastTurn << endl;
}
/*
###playAll Function
//playes the game untill the end
*/
void Game :: playAll(){

 if (gameOver){
        throw std :: logic_error ("Game ended, please restart the game for new");
    }
    while (this -> player1.stacksize() != 0 && this -> player2.stacksize() != 0){
        playTurn();
    }
    gameOver = true;

}
/*
###printWiner Function
// prints the name of the winning player
*/
void Game :: printWiner(){

    if (player1.cardesTaken() > player2.cardesTaken()){
        cout << player1.getName() + " wins! " << endl;
       
    }
    else if (player1.cardesTaken() < player2.cardesTaken()){
        cout << player2.getName() + " wins! " << endl;
      
    }
    else if(player1.cardesTaken() == player2.cardesTaken() && player1.getName() != player2.getName()){
        cout << " No one wins! There's a tie! " << endl;
    }



}
/*
###printLog Function
// prints all the turns played one line per turn (same format as game.printLastTurn())
*/
void Game :: printLog(){

    for (size_t i = 0 ; i < logOfGame.size() ; i++){
        string ans = logOfGame[i];
        cout << ans << endl;
    }
}

/*
###printStats Function
// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )*/
void Game :: printStats(){

    cout << player1.getName() << " won " << player1.getCountWins() << " times and got " << player1.cardesTaken() << " cards" << endl;
    cout << player2.getName() << " won " << player2.getCountWins() << " times and got " << player2.cardesTaken() << " cards" << endl;
    cout << "Overall there were " << (this -> countDraws) << " draws" << endl;
}

//help function for enum
string Game :: getCardValueName(int value) {

    switch (value) {
        case ACE:
            return "Ace";
        case JACK:
            return "Jack";
        case QUEEN:
            return "Queen";
        case KING:
            return "King";
        default:
            return std::to_string(value);
    }
}