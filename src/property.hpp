#include "cell.hpp"
#include "player.hpp"
#include <string>
#include <iostream>

class Property : public Cell
{
private:
    std::string name;
    int price;
    int rent;
    Player owner;
    
public:
    Property(std::string Name, int Price, int Rent, Player& player);
    void onLand() override{}
    virtual void buy();// устанавливает владельца и списывает деньги
    virtual void payRent() = 0; // платишь ренту
    virtual void getRent() const = 0; 
    virtual bool isOwned() const = 0;
    virtual Player *getOwner() const = 0;
    virtual void mortgage() = 0; //заложить дом
    virtual void unMortgage() = 0;// выкупить
    virtual void getPrice() const = 0;
    ~Property();
};