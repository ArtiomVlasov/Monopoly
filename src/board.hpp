#pragma once
#include <vector>
#include <memory>


class CellContent;
class Game;
class Property;
class Street;

class Board {
private:
    std::vector<std::shared_ptr<CellContent>> cells;
    Game *game;
public:
    Board(int numCells, Game *game);
    std::shared_ptr<CellContent> getCell(int position) const;
    Street* getStreetByName(std::string m);
    int getNextPosition(int currentPosition, int roll) const;
    std::vector<std::shared_ptr<CellContent>> getAllCells();
};
