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
    Property(CellType type,std::string Name, int Price, int Rent);
    void defaultAction(Player &player) override;
    void onLand() override;
    void startAuction(Property &property);
    void buy();                   // устанавливает владельца и списывает деньги
    virtual void payRent(Player &player); // платишь ренту
    virtual void getRent(Player &player) const = 0;
    virtual bool isOwned() const;
        virtual Player *getOwner() {
        return &owner;
    }
    virtual void mortgage();   // заложить недвижимость
    virtual void unMortgage(); // выкупить
    virtual int getPrice() const;
    virtual bool isFullListOfProperty(Player& player, CellType type) = 0;
    virtual int getAmountOfRent() const;
    int virtual getAmountOfMortgage() const;
    ~Property();
};
