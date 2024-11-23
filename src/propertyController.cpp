#include "propertySubClassesController.hpp"
#include "playerController.hpp"

int StreetController::handleStreetType(Street::Color color){
    switch (color) {
        case Street::Color::RedStreet:
            return 3;
        case Street::Color::YellowStreet:
            return 3;
        case Street::Color::GreenStreet:
            return 3;
        case Street::Color::BlueStreet:
            return 2;
        case Street::Color::BrownStreet:
           return 2;
        case Street::Color::WhiteStreet:
            return 3;
        case Street::Color::PinkStreet:
            return 3;
        case Street::Color::OrangeStreet:
            return 3;   
        default:
            return 1;
    }
}

bool StreetController::isFullListOfStreet(const Player *player, Street::Color color)
{
    int countQuantityProperty = 0;
    for (Property *property : player->getProperties())
    {
        Street *street = dynamic_cast<Street *>(property);
        if (street && street->getColor() == color)
        {
            countQuantityProperty++;
        }
    }
    return countQuantityProperty == handleStreetType(color);
}

int StreetController::getBuildingCost()
{
    return street->getPrice() / 2;
}

void StreetController::buildNewHouse()
{
    if (street->getLevelOfStreet() < 5)
    { 
        street->setHouseLevel(street->getLevelOfStreet()+1);
    }
}

void StreetController::demolishHouse()
{
    if (street->getLevelOfStreet() > 0)
    { 
        street->setHouseLevel(street->getLevelOfStreet()-1);
    }
}

int StreetController::calculateRent(Player *player, Street *street)
{
    int baseRent = street->getRent();
    return baseRent * (1 + street->getLevelOfStreet()); // Рента увеличивается с уровнем застройки
}

int RailwayController::calculateRent(Player *player, Railway *railway)
{
    int baseRent = railway->getRent();
    int ownedStations = playerController::getOwnedPropertyCount(CellType::PropRailway, player);
    return baseRent * ownedStations;
}

int UtilitiesController::calculateRent(Player *player, Utilities *utilities){
    int diceRoll = Game::getRollDice();
    int owned = playerController::getOwnedPropertyCount(CellType::PropUtilities, player);
    int multiplier = 0;
    if (owned == 1){
        multiplier = 4;
    }
    else if (owned == 2){
        multiplier = 10;
    }
    return diceRoll * multiplier;
}
