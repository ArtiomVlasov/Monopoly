#include "propertyController.hpp"
#include "playerController.hpp"
#include "TaxPrisonChance.hpp"
#include "prisonController.hpp"

PropertyController::PropertyController(Property *property):property(property){}

void PropertyController::payRent(Player *player, Property *property)
{
    int amount = property->getTotalRent(player);
    renderPayPlater(player, amount, property);
    playerController::playerPay(amount, player);
    playerController::playerReceive(amount, player);
}

void PropertyController::mortgageProperty(Player *player)
{
    property->setMortgageStatus(true);
    playerController::playerReceive(calculateMortgage(property), property->getOwner());
}

void PropertyController::markAsAvailable(Property *property)
{
    property->setMortgageStatus(false);
    property->setOwner(nullptr);
}

void PropertyController::unMortgageProperty(Player *player)
{
    if (!prisonController::isInJail(player) && player->getBalance() >= calculateUnMortgage())
    {
        playerController::playerPay(calculateUnMortgage(), player);
        property->setMortgageStatus(false);
    }
}

bool PropertyController::isOwnedProperty()
{
    if (property->getOwner())
    {
        return true;
    }
    return false;
}

int PropertyController::calculateMortgage(Property *property){
    return property->getRent() / 2;
}

int PropertyController::calculateUnMortgage()
{
    return (PropertyController::getProperty()->getRent() / 2 + PropertyController::getProperty()->getRent() * 0.1);
}

int PropertyController::getTotalPriceOfProperty(Player* player){
    int totalPrice = 0;
    for(Property *property: player->getListOfProperty()){
        totalPrice+= calculateMortgage(property);
    }
    return totalPrice;
}
