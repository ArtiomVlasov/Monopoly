#include "property.hpp"
#include "cell.hpp"
#include "game.hpp"
#include "TaxPrisonChance.hpp"
#include "propertySubClasses.hpp"

Board::Board(int numCells, Game *game):game(game)
{
    cells.push_back(std::make_shared<Street>(CellType::BrownStreet, "Old Kent Road", 60, 2));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>(CellType::BrownStreet, "Whitechapel Road", 60, 4));
    cells.push_back(std::make_shared<Tax>(200));
    cells.push_back(std::make_shared<Railway>(CellType::PropRailway, "King's Cross Station", 200, 25));

    cells.push_back(std::make_shared<Street>(CellType::WhiteStreet, "The Angel Islington", 100, 6));
    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>(CellType::WhiteStreet, "Euston Road", 100, 6));
    cells.push_back(std::make_shared<Street>(CellType::WhiteStreet, "Pentonville Road", 120, 8));
    //cells.push_back(std::make_shared<EmptyCell>(CellType::Empty));

    cells.push_back(std::make_shared<Street>(CellType::PinkStreet, "Pall Mall", 140, 10));
    cells.push_back(std::make_shared<Utilities>(CellType::PropUtilities, "Electric Company", 150, 1));
    cells.push_back(std::make_shared<Street>(CellType::PinkStreet, "Whitehall", 140, 10));
    cells.push_back(std::make_shared<Street>(CellType::PinkStreet, "Northumberland Avenue", 160, 12));
    cells.push_back(std::make_shared<Railway>(CellType::PropRailway, "Marylebone Station", 200, 25));

    cells.push_back(std::make_shared<Street>(CellType::OrangeStreet, "Bow Street", 180, 14));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>(CellType::OrangeStreet, "Marlborough Street", 180, 14));
    cells.push_back(std::make_shared<Street>(CellType::OrangeStreet, "Vine Street", 200, 16));
    //cells.push_back(std::make_shared<EmptyCell>(CellType::Empty));

    cells.push_back(std::make_shared<Street>(CellType::RedStreet, "Strand", 220, 18));
    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>(CellType::RedStreet, "Fleet Street", 220, 18));
    cells.push_back(std::make_shared<Street>(CellType::RedStreet, "Trafalgar Square", 240, 20));
    cells.push_back(std::make_shared<Railway>(CellType::PropRailway, "Fenchurch St Station", 200, 25));

    cells.push_back(std::make_shared<Street>(CellType::YellowStreet, "Leicester Square", 260, 22));
    cells.push_back(std::make_shared<Street>(CellType::YellowStreet, "Coventry Street", 260, 22));
    cells.push_back(std::make_shared<Utilities>(CellType::PropUtilities, "Water Works", 150, 1));
    cells.push_back(std::make_shared<Street>(CellType::YellowStreet, "Piccadilly", 280, 24));
    cells.push_back(std::make_shared<Prison>());

    cells.push_back(std::make_shared<Street>(CellType::GreenStreet, "Regent Street", 300, 26));
    cells.push_back(std::make_shared<Street>(CellType::GreenStreet, "Oxford Street", 300, 26));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>(CellType::GreenStreet, "Bond Street", 320, 28));
    cells.push_back(std::make_shared<Railway>(CellType::PropRailway, "Liverpool Street Station", 200, 25));

    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>(CellType::BlueStreet, "Park Lane", 350, 35));
    cells.push_back(std::make_shared<Tax>(100));
    cells.push_back(std::make_shared<Street>(CellType::BlueStreet, "Mayfair", 400, 50));
    //cells.push_back(std::make_shared<EmptyCell>(CellType::Empty));

}

std::shared_ptr<Cell> Board::getCell(int position) const
{
    return cells[position];
}

int Board::getNextPosition(int currentPosition, int roll) const
{
    return (currentPosition + roll) % cells.size();
}

std::vector<std::shared_ptr<Cell>> Board::getAllCells()
{
    return cells;
}
