#include "property.hpp"

class Railway : public Property
{
protected:
    int calculateRent(Player* player) override;
    

public:
    Railway(CellType type ,std::string name, int price, int rent); // : Property(name, price, rent){}
    ~Railway();
};

class Utilities : public Property
{
protected:
    int calculateRent(Player* player) override;

public:
    Utilities(CellType Type,std::string name, int price, int rent); //: Property(name, price, rent){}
    ~Utilities();
};

class Street : public Property
{
private:
    int level;

protected:
    int calculateRent(Player* player) override;

public:
    Street(CellType type, std::string name, int price, int rent, CellType color);
    int getBuildingCost();
    void buildNewHouse();
    void demolishHouse();
    int getLevelOfStreet();
    ~Street();
};
