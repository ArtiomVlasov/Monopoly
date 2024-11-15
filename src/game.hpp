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
    bool isGameOver() const;
    int getRollDice();
    void sellProperty(Player *player);
    int rollDice();

private:
    void caseMapToAction(int a);
    int playerTurn;
    int firstValue;
    int secondValue;
    std::vector<Player *> players;
    Board *board;
    int numPlayers;
    void nextPlayer();
};
