#include <player.hpp>
#include <propertySubClasses.hpp>
#include <cell.hpp>

Player::Player(std::string name) : name(name), balance(2000), position(0), inJail(false), bankrupt(false), numMovesInPrison(0), listOfProperty() {}

int Player::getTotalPriceOfProperty()
{
    return totalPriceOfProperty;
}

void Player::makeMove(int steps)
{
    position = (position + steps) % 40;
}

void Player::pay(int amount)
{
    balance -= amount;
}

void Player::receive(int amount)
{
    balance += amount;
}

void Player::addProperty(Property *property)
{
    totalPriceOfProperty += property->calculateMortgage();
    property->setOwner(*this);
    listOfProperty.push_back(property);
}

bool Player::canAfford(int amount) const
{
    if (amount > balance)
    {
        if (amount > balance + totalPriceOfProperty)
        {
            return false;
        }
        else {} // нужно вернуть какое то сообщение о том что необходи продать имущество чтобы заплатить
    }
    return true;
}

void Player::declareBankruptcy(Player *creditor)
{
    bankrupt = true;

    if (creditor)
    {
        for (Property *property : listOfProperty)
        {
            property->setOwner(*creditor);
            creditor->addProperty(property);
        }
        creditor->receive(balance);
    }
    else
    {
        for (Property *property : listOfProperty)
        {
            property->markAsAvailable();
        }
    }
    listOfProperty.clear();
    balance = 0;
}

/*void Player::mortgageProperty(Property& property){
    if(property.)
}*/

int Player::getBalance() const
{
    return balance;
}

std::string Player::getName() const
{
    return name;
}

int Player::getPosition() const
{
    return position;
}

const std::vector<Property *> &Player::getProperties() const
{
    return listOfProperty;
}

bool Player::isBankrupt() const
{
    return bankrupt;
}

bool Player::isInJail() const
{
    return inJail;
}

void Player::sendToJail()
{
    position = 10;
    numMovesInPrison = 1;
    inJail = true;
}

void Player::releaseFromJail()
{
    inJail = false;
}

bool Player::canBuildOn(Property *property) const
{
    if (property->getType() == CellType::Railway or property->getType() == CellType::Utilities)
    {
        return false;
    }
}

void Player::buildStructure(Street *street)
{
    if (!canBuildOn)
    {
        std::cout << "You can't build on this street, because you don't have all streets of this colour" << std::endl;
        return;
    }
    street->buildNewHouse();
}

void Player::destroyStructure(Street &street)
{
    if (street.getLevelOfStreet() == 1)
    {
        std::cout << "You can't destroy house on this street, because it already base level" << std::endl;
        return;
    }
    street.demolishHouse();
}

void Player::incrementNumMovesInPrison()
{
    numMovesInPrison++;
}

int Player::getNumMovesInPrison()
{
    return numMovesInPrison;
}

int Player::makeBid(int currentHighestBid)
{
    int bid;
    std::cin >> bid; // не знаю наверно верно
    if (bid == -1)
    {
        return -1;
    }

    if (bid > currentHighestBid)
    {
        return bid;
    }
    else
    {

        return makeBid(currentHighestBid);
    }
}

int Player::makeDecision()
{
    int decision;
    std::cin >> decision;
    return decision;
}

void Player::startAuction(Property *property, const std::vector<Player *> &players)
{
    int highestBid = 0;
    Player *highestBidder = nullptr;

    bool auctionActive = true;
    while (auctionActive)
    {
        auctionActive = false;

        for (Player *player : players)
        {
            if (player != this)
            {
                int bid = player->makeBid(highestBid);

                if (bid > highestBid && player->canAfford(bid))
                {
                    highestBid = bid;
                    highestBidder = player;
                    auctionActive = true;
                }
                else if (bid == -1)
                {
                    //???????????????
                }
            }
        }
    }
    if (highestBidder)
    {
        highestBidder->pay(highestBid);
        highestBidder->addProperty(property);
    }
    else
    {
        //???????????????
    }
}

void Player::buy(Property &property)
{
    pay(property.getPrice());

    property.setOwner(*this);

    listOfProperty.push_back(&property);
}