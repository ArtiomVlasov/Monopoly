#include "property.hpp"
#pragma once
class Railway : public Property
{
protected:
    int getTotalRent(Player *player) override;

public:
    Railway(std::string name, int price, int rent); // : Property(name, price, rent){}
    ~Railway();
};

class Utilities : public Property
{
protected:
    int getTotalRent(Player *player) override;

public:
    Utilities(std::string name, int price, int rent); //: Property(name, price, rent){}
    ~Utilities();
};

class Street : public Property
{
protected:
    int getTotalRent(Player *player) override;

public:
    enum class Color
    {
        RedStreet,
        YellowStreet,
        GreenStreet,
        BlueStreet,
        BrownStreet,
        WhiteStreet,
        PinkStreet,
        OrangeStreet
    };
    Street(std::string name, int price, int rent, Color color);
    //int getBuildingCost();
    //bool isFullListOfStreet(const Player *player, Color color);
    //void buildNewHouse();
    //void demolishHouse();
    void setHouseLevel(int level);
    //int handleCellType(Color color);
    Color getColor();
    int getLevelOfStreet();
    ~Street();

private:
    int level;
    Color color;
};
