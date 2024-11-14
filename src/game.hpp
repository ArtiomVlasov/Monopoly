#include <vector>
#include <memory>
#include "board.hpp"

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
    
private:
    int currentPlayerIndex;
    std::vector<Player *> players;
    Board board;
    int rollDice() const;
    void nextPlayer();           
};