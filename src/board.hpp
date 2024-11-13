#include <vector>
#include <memory>

class Cell;

class Board {
private:
    std::vector<std::shared_ptr<Cell>> cells;
public:
    Board(int numCells);
    Cell* getCell(int position) const;
    int getNextPosition(int currentPosition, int roll) const;
    void addCell(std::shared_ptr<Cell> cell);
    

};