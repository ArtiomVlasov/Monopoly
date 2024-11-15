#include "propertySubClasses.hpp"
#include "player.hpp"

Railway::Railway(CellType type, std::string name, int price, int rent)
    : Property(type, name, price, rent, nullptr) {}

int Railway::calculateRent(Player *player)
{
    int baseRent = getRent();
    int ownedStations = player->getOwnedPropertyCount(CellType::PropRailway);
    return baseRent * ownedStations; // рента увеличивается вдвое за каждую станцию
}

Railway::~Railway() {}

Utilities::Utilities(CellType type, std::string name, int price, int rent)
    : Property(type, name, price, rent, nullptr) {}

int Utilities::calculateRent(Player *player)
{
    int diceRoll = player->getLastDiceRoll();
    int multiplier = this->isFullListOfProperty(player, this-> getType()) ? 10 : 4;
    return diceRoll * multiplier;
}

Utilities::~Utilities() {}

int Street::calculateRent(Player *player)
{
    int baseRent = getRent();
    return baseRent * (1 + level); // Рента увеличивается с уровнем застройки
}

Street::Street(CellType type, std::string name, int price, int rent)
    : Property(type, name, price, rent, nullptr), level(0) {}

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
