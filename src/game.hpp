#include <vector>
#include <memory>
#include "board.hpp"
#pragma once
class Player;

class Game {
public:
    typedef struct gameRollValue
    {
        int firstValue;
        int secondValue;
    }gameRollValue;
    
    Game(int numPlayers, int numCells);
    void start();
    std::vector<Player *> getListOfPlayers();
    void takeTurn();
    int getBoardSize();
    Board getBoard();
    bool isGameOver() const; 
    void sellProperty();

private:
    int playerTurn;
    std::vector<Player *> players;
    Board* board;
    int numPlayers;
    int rollDice(gameRollValue gamerollvalue) const;
    void nextPlayer();           
};
