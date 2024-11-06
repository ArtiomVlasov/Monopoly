#include <vector>
#include <memory>
#include <player.hpp>
#include <board.hpp>

class Game {
public:
    Game(int numPlayers, int numCells);
    void start();           
    void takeTurn();        
    bool isGameOver() const; 
    
private:
    int currentPlayerIndex;
    std::vector<Player> players;
    Board board;
    int rollDice() const;
    void nextPlayer();           
};