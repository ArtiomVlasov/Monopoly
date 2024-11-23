#include <vector>
#include <memory>
#pragma once

class Cell;
class Game;

class Board {
private:
    std::vector<std::shared_ptr<Cell>> cells;
    Game *game;
public:
    static Property* getPropertyFromCell(int a);
    Board();
    Board(int numCells, Game *game);
    std::shared_ptr<Cell> getCell(int position) const;
    Street* getStreetByName(std::string m);
    int getNextPosition(int currentPosition, int roll) const;
    std::vector<std::shared_ptr<Cell>> getAllCells();
};
