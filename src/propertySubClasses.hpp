#include "property.hpp"

class Railway : public Property
{
protected:
    int calculateRent(Player* player) override;
    

public:
    Railway(CellType type ,std::string name, int price, int rent); // : Property(name, price, rent){}
    int calculateMortgage() override;
    int calculateUnMortgage() override;
    ~Railway();
};

class Utilities : public Property
{
protected:
    int calculateRent(Player* player) override;

public:
    Utilities(CellType Type,std::string name, int price, int rent); //: Property(name, price, rent){}
    int calculateMortgage() override;
    int calculateUnMortgage() override;
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
    int calculateMortgage() override;
    int calculateUnMortgage() override;
    void buildNewHouse();
    bool CanBuildHouse(Player &player);
    void demolishHouse();
    int getLevelOfStreet();
    ~Street();
};
