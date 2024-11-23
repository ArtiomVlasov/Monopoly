#include <vector>
#include <memory>
#include "board.hpp"
class prisonController;
class playerController;
class StreetController;
#pragma once
class Player;

class Game {
public:
    
    Game(int numPlayers, int numCells);
    void start();
    std::vector<Player *> getListOfPlayers();
    void takeTurn(prisonController *pc, playerController* playercontroller, prisonController* prisoncontroller);
    int getBoardSize();
    Board getBoard();
    bool isGameOver() const; 
    void sellProperty(Player* player);
    static int getRollDice();
    int rollDice();
    static bool isBankruptPlayer(Player* player);
    static void addBankruptPlayers(Player* player);
    bool isAllPlayersIsBankrupt;
private:
    static std::vector<Player *> bankruptPlayers;
    void caseMapToAction(int a, Player* player, playerController* playercontooller, prisonController* prisoncontroller);
    static int firstValue;
    static int secondValue;
    int playerTurn;
    std::vector<Player *> players;
    Board* board;
    int numPlayers;
    void nextPlayer();           
};
