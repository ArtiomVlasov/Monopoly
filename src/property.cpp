#include "property.hpp"
#include "player.hpp"


Property::Property(CellType type, std::string Name, int Price, int Rent, Player *owner)
    : Cell(type), name(Name), price(Price), rent(Rent), owner(owner), isMortgage(false) {}

void Property::defaultAction(Player *player, Game* game)
{
    if (player->getName() != owner->getName() && (isMortgage == false))
    {
        payRent(player);
    }
    else if(player->getName() != owner->getName() && (isMortgage == true)){
        std::cout << player->getName();
    }
    else if (!player->canAfford(price))
    
    {
        player->startAuction(this, game->getListOfPlayers());
        return;
    }
    int ans = player->makeDecision();
    switch (ans)
    {
    case 0: // может купить
        player->buy(*this);
        // player.buy()
    case 1: // акуцион
        player->startAuction(this, game->getListOfPlayers());
        return;
    }
}

void Property::setOwner(Player *newOwner)
{
    owner = newOwner;
}

bool Property::isMortgaged()
{
    return isMortgage;
}

void Property::markAsAvailable(){
    isMortgage = false;
    //owner = &Player();
}

void Property::payRent(Player *player)
{
    int amount = calculateRent(player);
    if (player->canAfford(amount))
    {
        player->pay(amount);
        owner->receive(amount);
    }
    else
    {
        player->declareBankruptcy(owner);
    }
}

int Property::getRent() const
{
    return this->rent;
}

bool Property::isOwned()
{
    return !this->name.empty();
}

int Property::getPrice() const
{
    return this->price;
}

std::string Property::getName() const{
    return name;
}

void Property::mortgage()
{
    this->owner->setBalance(this->owner->getBalance() * 1.1);
}

void Property::unMortgage(Player *player)
{
    if (!player->isInJail() && !player->isBankrupt() && player->getBalance() == price * 1.1)
    {
        player->setBalance(player->getBalance() - this->price * 1.1);
        this->owner = player;
    }
}

/*bool Property::isFullListOfProperty(Player &player, CellType type, CellType proptype)
{
    int countQuantityPropertys = 0;
    for (int index = 0; index < player.getQuantityOfProperty(); index++)
    {
        if (player.getCellTypeInListOfProperty(index) == type)
        {
            countQuantityPropertys++;
        }
    }
    return countQuantityPropertys == handleCellType(proptype);
}*/

int Property::getAmountOfRent() const
{
    return this->rent;
}

int Property::getAmountOfMortgage() const
{
    return 0; // ????
}

Property::~Property()
{
}
