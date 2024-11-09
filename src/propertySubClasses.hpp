#include <property.hpp>

class Railway : public Property
{
protected:
    int calculateRent() override;
    int calculateMortgage() override;
    int calculateUnMortgage() override;

public:
    Railway(CellType type ,std::string name, int price, int rent); // : Property(name, price, rent){}
    void getRent(Player &player) const override;
    ~Railway();
};

class Utilities : public Property
{
protected:
    int calculateRent() override;
    int calculateMortgage() override;
    int calculateUnMortgage() override;

public:
    Utilities(CellType Type,std::string name, int price, int rent); //: Property(name, price, rent){}
    void getRent(Player &player) const override;
    ~Utilities();
};

class Street : public Property
{
private:
    int level;

protected:
    int calculateRent() override;
    int calculateMortgage() override;
    int calculateUnMortgage() override;

public:
    Street(CellType type, std::string name, int price, int rent, PropertyType color);
    void buildNewHouse();
    bool CanBuildHouse(Player &player);
    void demolishHouse();
    int getLevelOfStreet();
    ~Street();
};
