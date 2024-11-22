#include "propertyController.hpp"
#include "playerController.hpp"
#include "TaxPrisonChance.hpp"
#include "prisonController.hpp"

PropertyController::PropertyController(Property *property):property(property){}

void PropertyController::payRent(Player *player, Property *property)
{
    int amount = property->getTotalRent(player);
    std::cout << "Игрок " << player->getName() << " платит ренту в размере " << amount << " монет игроку " << property->getOwner()->getName() << ".\n";
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

void PropertyController::unMortgageProperty(Player *player, prisonController * prisonCtrl)
{
    if (!prisonCtrl->isInJail(player) && player->getBalance() >= calculateUnMortgage())
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
    return (property->getRent() / 2 + property->getRent() * 0.1);
}

int PropertyController::getTotalPriceOfProperty(Player* player){
    int totalPrice = 0;
    for(Property *property: player->getListOfProperty()){
        totalPrice+= calculateMortgage(property);
    }
    return totalPrice;
}