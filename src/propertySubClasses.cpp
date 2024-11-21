#include "propertySubClasses.hpp"
#include "player.hpp"

Railway::Railway(std::string name, int price, int rent)
    : Property(CellType::PropRailway, name, price, rent, nullptr) {}

int Railway::calculateRent(Player *player)
{
    int baseRent = getRent();
    int ownedStations = player->getOwnedPropertyCount(CellType::PropRailway);
    return baseRent * ownedStations; // рента увеличивается вдвое за каждую станцию
}

Railway::~Railway() {}

Utilities::Utilities(std::string name, int price, int rent)
    : Property(CellType::PropUtilities, name, price, rent, nullptr) {}

int Utilities::calculateRent(Player *player)
{
    int diceRoll = player->getLastDiceRoll();
    int owned = player->getOwnedPropertyCount(CellType::PropUtilities);
    int multiplier = 0;
    if (owned == 1){
        multiplier = 4;
    }
    else if (owned == 2){
        multiplier = 10;
    }
    return diceRoll * multiplier;
}

Utilities::~Utilities() {}

int Street::calculateRent(Player *player)
{
    int baseRent = getRent();
    return baseRent * (1 + level); // Рента увеличивается с уровнем застройки
}

Street::Street(std::string name, int price, int rent, Color color)
    : Property(CellType::Street, name, price, rent, nullptr), level(0),  color(color) {}

int Street::getBuildingCost()
{
    return this->getPrice() / 2;
}

void Street::buildNewHouse()
{
    if (level < 5)
    { 
        level++;
    }
}

void Street::demolishHouse()
{
    if (level > 0)
    {
        level--;
    }
}

int Street::getLevelOfStreet()
{
    return level;
}

Street::~Street() {}

int Street::handleCellType(Color color) {
    switch (color) {
        case Color::RedStreet:
            return 3;
        case Color::YellowStreet:
            return 3;
        case Color::GreenStreet:
            return 3;
        case Color::BlueStreet:
            return 2;
        case Color::BrownStreet:
           return 2;
        case Color::WhiteStreet:
            return 3;
        case Color::PinkStreet:
            return 3;
        case Color::OrangeStreet:
            return 3;   
        default:
            return 1;
    }
}

Street::Color Street::getColor(){
    return color;
}

bool Street::isFullListOfStreet(const Player *player, Color color)
{
    int countQuantityProperty = 0;
    for (Property *property : player->getProperties())
    {
        Street *street = dynamic_cast<Street *>(property);
        if (street->getColor() == color)
        {
            countQuantityProperty++;
        }
    }
    return countQuantityProperty == handleCellType(color);
}
