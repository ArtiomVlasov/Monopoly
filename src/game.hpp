#pragma once
#include <vector>
#include <memory>
#include "board.hpp"

class prisonController;
class playerController;
class StreetController;
class Player;

class Game {
public:
    
    Game(int numPlayers, int numCells);
    void start();
    std::vector<Player *> getListOfPlayers();
    void takeTurn(prisonController *pc, playerController *plrCntl);
    int getBoardSize();
    Board getBoard();
    bool isGameOver() const; 
    void sellProperty(Player *player, playerController *plrCntl);
     int getRollDice();
    std::vector<Player *> getBankruptPlayers();
    int rollDice();
     bool isBankruptPlayer(Player* player);
    void addBankruptPlayers(Player* player);
    bool isAllPlayersIsBankrupt;
private:
     std::vector<Player *> bankruptPlayers;
    void caseMapToAction(int a, Player* player, playerController* playercontroller, prisonController* prisoncontroller);
     int firstValue;
     int secondValue;
    int playerTurn;
    std::vector<Player *> players;
    Board* board;
    int numPlayers;
    void nextPlayer();           
};
