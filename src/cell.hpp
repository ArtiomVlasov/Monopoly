#include "player.hpp"

enum class CellType { Property, Chance, Tax, Prison, Street, Railway, Utilities};
enum class PropertyType { // надо подумать можно ли как-то еще это реализовать
    RedStreet,
    YellowStreet,
    GreenStreet,
    BlueStreet,
    BrownStreet,
    WhiteStreet,
    PinkStreet,
    OrangeStreet,
    PropRailway,
    PropUtilities
};

int handleCellType(PropertyType propertyType) {
    switch (propertyType) {
        case PropertyType::RedStreet:
            return 3;
        case PropertyType::YellowStreet:
            return 3;
        case PropertyType::GreenStreet:
            return 3;
        case PropertyType::BlueStreet:
            return 2;
        case PropertyType::BrownStreet:
           return 2;
        case PropertyType::WhiteStreet:
            return 3;
        case PropertyType::PinkStreet:
            return 3;
        case PropertyType::OrangeStreet:
            return 3;
        case PropertyType::PropRailway:
            return 4;   
        default:
            return 1;
    }
}
class Cell
{
protected:
    CellType type;
public:
    Cell(CellType t);
    virtual void onLand() = 0; // сообщает на какую клетку попал
    CellType getType() const;
    virtual void defaultAction(Player &player) = 0;
    virtual ~Cell() = default;
    bool isEmpty();
};
