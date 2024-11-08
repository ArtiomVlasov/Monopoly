#include "property.hpp"
#include "cell.hpp"
#include "board.hpp"

Property::Property(CellType type, std::string Name, int Price, int Rent, Player owner) 
    : name(Name), price(Price), rent(Rent), type(type), owner(owner) {}

void Property::buy(Player &player) {
    this->owner = player;
    player.setBalance(this->rent);
}

void Property::payRent(Player &player) {
    player.setBalance(getAmountOfRent());
}

int Property::getRent() {
    return this->rent;
}

bool Property::isOwned() {
    return !this->name.empty();
}

int Property::getPrice() const {
    return this->price;
}

void Property::mortgage() {
    this->owner.setBalance(this->owner.getBalance() * 1.1);
    this->owner = Player();
}

void Property::unMortgage(Player &player) {
    if(!player.isInJail() && !player.isBankrupt() && player.getBalance() == price*1.1) {
        player.setBalance(player.getBalance() - this->price * 1.1);
        this->owner = player;
    }
}

bool Property::isFullListOfProperty(Player& player, CellType type, PropertyType proptype) {
    int countQuantityPropertys = 0;
    for (int index = 0; index < player.getQuantityOfProperty(); index++) {
        if (player.getCellTypeInListOfProperty(index) == type) {
            countQuantityPropertys++;
        }
    }
    return countQuantityPropertys == handleCellType(proptype);
}
