#include <player.hpp>
#include <propertySubClasses.hpp>
#include <cell.hpp>


Player::Player(std::string name) : name(name), balance(2000), position(0), inJail(false), bankrupt(false), numMovesInPrison(0), listOfProperty() {}

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
    listOfProperty.push_back(property);
}

bool Player::canAfford(int amount) const
{
    if (amount > balance)
    {
        return false;
    }
    return true;
}

void Player::declareBankruptcy()
{
    bankrupt = true;
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