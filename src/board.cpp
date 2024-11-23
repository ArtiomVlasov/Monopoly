#include "property.hpp"
#include "cell.hpp"
#include "game.hpp"
#include "TaxPrisonChance.hpp"
#include "propertySubClasses.hpp"

Board::Board(int numCells, Game *game):game(game)
{
    cells.push_back(std::make_shared<Street>("Old Kent Road", 60, 2, Street::Color::BrownStreet));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>("Whitechapel Road", 60, 4, Street::Color::BrownStreet));
    cells.push_back(std::make_shared<Tax>(200));
    cells.push_back(std::make_shared<Railway>("King's Cross Station", 200, 25));

    cells.push_back(std::make_shared<Street>("The Angel Islington", 100, 6, Street::Color::WhiteStreet));
    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>("Euston Road", 100, 6,  Street::Color::WhiteStreet));
    cells.push_back(std::make_shared<Street>("Pentonville Road", 120, 8,  Street::Color::WhiteStreet));
    cells.push_back(std::make_shared<EmptyCell>());

    cells.push_back(std::make_shared<Street>("Pall Mall", 140, 10, Street::Color::PinkStreet));
    cells.push_back(std::make_shared<Utilities>( "Electric Company", 150, 1));
    cells.push_back(std::make_shared<Street>("Whitehall", 140, 10, Street::Color::PinkStreet));
    cells.push_back(std::make_shared<Street>("Northumberland Avenue", 160, 12, Street::Color::PinkStreet));
    cells.push_back(std::make_shared<Railway>( "Marylebone Station", 200, 25));

    cells.push_back(std::make_shared<Street>("Bow Street", 180, 14, Street::Color::OrangeStreet));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>("Marlborough Street", 180, 14, Street::Color::OrangeStreet));
    cells.push_back(std::make_shared<Street>("Vine Street", 200, 16, Street::Color::OrangeStreet));
    cells.push_back(std::make_shared<EmptyCell>());

    cells.push_back(std::make_shared<Street>("Strand", 220, 18, Street::Color::RedStreet));
    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>("Fleet Street", 220, 18, Street::Color::RedStreet));
    cells.push_back(std::make_shared<Street>("Trafalgar Square", 240, 20, Street::Color::RedStreet));
    cells.push_back(std::make_shared<Railway>( "Fenchurch St Station", 200, 25));

    cells.push_back(std::make_shared<Street>("Leicester Square", 260, 22, Street::Color::YellowStreet));
    cells.push_back(std::make_shared<Street>("Coventry Street", 260, 22, Street::Color::YellowStreet));
    cells.push_back(std::make_shared<Utilities>( "Water Works", 150, 1));
    cells.push_back(std::make_shared<Street>("Piccadilly", 280, 24, Street::Color::YellowStreet));
    cells.push_back(std::make_shared<Prison>());

    cells.push_back(std::make_shared<Street>("Regent Street", 300, 26, Street::Color::GreenStreet));
    cells.push_back(std::make_shared<Street>("Oxford Street", 300, 26, Street::Color::GreenStreet));
    cells.push_back(std::make_shared<PublicTreasury>());
    cells.push_back(std::make_shared<Street>("Bond Street", 320, 28, Street::Color::GreenStreet));
    cells.push_back(std::make_shared<Railway>( "Liverpool Street Station", 200, 25));

    cells.push_back(std::make_shared<Chance>(game));
    cells.push_back(std::make_shared<Street>("Park Lane", 350, 35, Street::Color::BlueStreet));
    cells.push_back(std::make_shared<Tax>(100));
    cells.push_back(std::make_shared<Street>("Mayfair", 400, 50, Street::Color::BlueStreet));
    cells.push_back(std::make_shared<EmptyCell>());

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


Street* Board::getStreetByName(std::string nameStreet) {
  for (const auto& cell : getAllCells()) { // Используем const auto& для избежания копирования
        Street* street = dynamic_cast<Street*>(cell.get());
        if (street != nullptr) {
            if (street->getName() == nameStreet) {
                return street;
            }
        }
    }
    return nullptr;
}
