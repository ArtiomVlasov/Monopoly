#include <vector>
#include <memory>
#include "board.hpp"
#pragma once
class Player;

class Game
{
public:
    Game(int numPlayers, int numCells);
    void start();
    std::vector<Player *> getListOfPlayers();
    void takeTurn();
    int getBoardSize();
    Board getBoard();
    bool isGameOver() const;
    int getRollDice();
    void sellProperty();

private:
    int playerTurn;
    int firstDiceValue;
    int secondDiceValue;
    std::vector<Player *> players;
    Board *board;
    int numPlayers;
    int rollDice();
    void nextPlayer();
};
