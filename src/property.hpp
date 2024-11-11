#include "cell.hpp"
#include <string>
#include <game.hpp>
#include <iostream>

class Player;

class Property : public Cell
{
private:
    std::string name;
    int price;
    int rent;
    Player owner;
    bool isMortgage;

protected:
    int virtual calculateRent(Player &player);
    

public:
    Property(CellType type,std::string Name, int Price, int Rent, Player owner);
    void defaultAction(Player &player, Game& game) override;
    virtual void payRent(Player &player); // платишь ренту
    int getRent() const;
    virtual bool isOwned();
        virtual Player *getOwner() {
        return &owner;
    }
    int virtual calculateMortgage();
    int virtual calculateUnMortgage();
    void setOwner(Player& newOwner);
    virtual void mortgage();   // заложить недвижимость
    virtual void unMortgage(Player &player); // выкупить
    void markAsAvailable();
    bool isMortgaged();
    virtual int getPrice() const;
    std::string getName() const
    virtual bool isFullListOfProperty(Player& player, CellType type, PropertyType proptype) = 0;
    virtual int getAmountOfRent() const;
    int virtual getAmountOfMortgage() const;
    ~Property();
};
