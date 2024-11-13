#include "cell.hpp"

Cell::Cell(CellType type):type(type){}

CellType Cell::getType() const {
    return type;
}

int handleCellType(CellType propertyType) {
    switch (propertyType) {
        case CellType::RedStreet:
            return 3;
        case CellType::YellowStreet:
            return 3;
        case CellType::GreenStreet:
            return 3;
        case CellType::BlueStreet:
            return 2;
        case CellType::BrownStreet:
           return 2;
        case CellType::WhiteStreet:
            return 3;
        case CellType::PinkStreet:
            return 3;
        case CellType::OrangeStreet:
            return 3;
        case CellType::PropRailway:
            return 4;   
        default:
            return 1;
    }
}
