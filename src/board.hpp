#include <vector>
#include <memory>
#pragma once

class Cell;

class Board {
private:
    std::vector<std::shared_ptr<Cell>> cells;
    
public:
    Board();
    Board(int numCells);
    std::shared_ptr<Cell> getCell(int position) const;
    int getNextPosition(int currentPosition, int roll) const;
    const std::vector<std::unique_ptr<Cell>>& getAllCells() const;
};
