#include <board.hpp>

#include "cell.hpp"

Board::Board(int numCells)
{
    for (int index = 0; index < numCells; index++)
    {
        if (index == 21 || (index > 22 && index < 25))
        {
            cells.push_back(std::make_shared<Cell>(CellType::RedStreet, index));
        }
        else if (index == 29 || index == 27 || index == 26)
        {
            cells.push_back(std::make_shared<Cell>(CellType::YellowStreet, index));
        }
        else if (index == 31 || index == 32 || index == 34)
        {
            cells.push_back(std::make_shared<Cell>(CellType::GreenStreet));
        }
        else if (index == 39 || index == 37)
        {
            cells.push_back(std::make_shared<Cell>(CellType::BlueStreet, index));
        }
        else if (index == 39 || index == 37)
        {
            cells.push_back(std::make_shared<Cell>(CellType::BrownStreet, index));
        }
        else if (index == 19 || index == 18 || index == 16)
        {
            cells.push_back(std::make_shared<Cell>(CellType::OrangeStreet, index));
        }
        else if (index == 11 || index == 13 || index == 14)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PinkStreet, index));
        }
        else if (index == 9 || index == 8 || index == 6)
        {
            cells.push_back(std::make_shared<Cell>(CellType::WhiteStreet, index));
        }
        else if (index == 5 || index == 15 || index == 25 || index == 35)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PropRailway, index));
        }
        else if (index == 2 || index == 18)
        {
            cells.push_back(std::make_shared<Cell>(CellType::PropUtilities, index));
        }
        else if (index == 7 || index == 22 || index == 36)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Chance, index));
        }
        else if (index == 34)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Tax, index));
        }
        else if (index == 10)
        {
            cells.push_back(std::make_shared<Cell>(CellType::Prison, index));
        }
        else
        {
            cells.push_back(std::make_shared<Cell>(CellType::publicTreasury, index));
        }
    }
}


std::shared_ptr<Cell> Board::getCell(int position) const {
    for (int index = 0; index < cells.size(); index++) {
        if (cells[index]->getPosition() == position) {
            return cells[index];
        }
    }
}



