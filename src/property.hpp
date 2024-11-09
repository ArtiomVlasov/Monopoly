#include "cell.hpp"
#include <string>
#include <iostream>

class Player;

class Property : public Cell
{
private:
    std::string name;
    int price;
    int rent;
    Player owner;

protected:
    int virtual calculateRent();
    int virtual calculateMortgage();
    int virtual calculateUnMortgage();

public:
    Property(CellType type,std::string Name, int Price, int Rent, Player owner);
    void defaultAction(Player &player) override;
    void startAuction(Property &property);
    void buy(Player &player);                   // устанавливает владельца и списывает деньги
    virtual void payRent(Player &player); // платишь ренту
    virtual void getRent(Player &player) const = 0;
    virtual bool isOwned();
        virtual Player *getOwner() {
        return &owner;
    }
    virtual void mortgage();   // заложить недвижимость
    virtual void unMortgage(Player &player); // выкупить
    virtual int getPrice() const;
    virtual bool isFullListOfProperty(Player& player, CellType type, PropertyType proptype) = 0;
    virtual int getAmountOfRent() const;
    int virtual getAmountOfMortgage() const;
    ~Property();
};
