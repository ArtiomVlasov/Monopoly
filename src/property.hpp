#include "cell.hpp"
#include <string>
#include "game.hpp"
#include <iostream>
#pragma once

class Property : public Cell
{
private:
    std::string name;
    int price;
    int rent;
    Player *owner;
    bool isMortgage;

protected:
    virtual int calculateRent(Player *player) = 0;
public:
    Property(CellType type,std::string Name, int Price, int Rent, Player *owner);
    virtual void defaultAction(Player *player, Game* game) override;
    void payRent(Player *player); // платишь ренту
    int getRent() const;
    bool isOwned();
    Player *getOwner();
    int calculateMortgage();
    int calculateUnMortgage();
    void setOwner(Player *newOwner);
    void mortgage();   // заложить недвижимость
    void unMortgage(Player *player); // выкупить
    void markAsAvailable();
    bool isMortgaged();
    int getPrice() const;
    std::string getName() const;
    bool isFullListOfProperty(Player *player, CellType type);
    bool isStreet();
};
