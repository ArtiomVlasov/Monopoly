#include <vector>
#include <memory>
#include "board.hpp"
#pragma once
class Player;

class Game {
public:

    Game(int numPlayers, int numCells);
    void start();
    std::vector<Player *> getListOfPlayers();
    void takeTurn();
    int getBoardSize();
    Board getBoard();
    bool isGameOver() const; 
    void sellProperty(Player* player);
    int getRollDice();
    int rollDice();
    static bool isBankruptPlayer(Player* player);
    static void addBankruptPlayers(Player* player);
private:
    static std::vector<Player *> bankruptPlayers;
    void caseMapToAction(int a);
    int firstValue;
    int secondValue;
    int playerTurn;
    std::vector<Player *> players;
    Board* board;
    int numPlayers;
    void nextPlayer();           
};
