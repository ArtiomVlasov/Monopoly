#include "board.hpp"
#include "property.hpp"
#include "cell.hpp"
#include "propertySubClasses.hpp"

Board::Board(int numCells)
{
    for (int index = 0; index < numCells; index++)
    {
        // Property(CellType type,std::string Name, int Price, int Rent, Player *owner);
        if (index == 21 || (index > 22 && index < 25))
        {
            cells.push_back(std::make_shared<Street>(CellType::RedStreet, "NULL", 100, 100));
        }
        else if (index == 29 || index == 27 || index == 26)
        {
            cells.push_back(std::make_shared<Cell>(CellType::YellowStreet));
        }
        else if (index == 31 || index == 32 || index == 34)
        {
            cells.push_back(std::make_shared<Cell>(CellType::GreenStreet));
        }
        else if (index == 39 || index == 37)
        {
            cells.push_back(std::make_shared<Cell>(CellType::BlueStreet));
        }
        else if (index == 39 || index == 37)
        {
            cells.push_back(std::make_shared<Cell>(CellType::BrownStreet));
        }
        else if (index == 19 || index == 18 || index == 16)
        {
            cells.push_back(std::make_shared<Cell>(CellType::OrangeStreet));
        }
        else if (index == 11 || index == 13 || index == 14)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PinkStreet));
        }
        else if (index == 9 || index == 8 || index == 6)
        {
            cells.push_back(std::make_shared<Cell>(CellType::WhiteStreet));
        }
        else if (index == 5 || index == 15 || index == 25 || index == 35)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PropRailway));
        }
        else if (index == 2 || index == 18)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PropUtilities));
        }
        else if (index == 7 || index == 22 || index == 36)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Chance));
        }
        else if (index == 34)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Tax));
        }
        else if (index == 10)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Prison));
        }
        else
        {
            cells.push_back(std::make_shared<Cell>(CellType::publicTreasury));
        }
    }
}

std::shared_ptr<Cell> Board::getCell(int position) const
{
    return cells[position];
}

int Board::getNextPosition(int currentPosition, int roll) const
{
    return (currentPosition + roll) % cells.size();
}

const std::vector<std::unique_ptr<Cell>> &Board::getAllCells() const
{
    static std::vector<std::unique_ptr<Cell>> uniqueCells;
    uniqueCells.clear();
    for (const auto &sharedPtr : cells)
    {
        if (sharedPtr)
        {
            uniqueCells.push_back(std::make_unique<Cell>(*sharedPtr));
        }
    }
    return uniqueCells;
}
