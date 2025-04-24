#include "cellContent.hpp"
#include <iostream>
CellContent::CellContent(CellType type):type(type){}

CellType CellContent::getType() const {
    return type;
}

void CellContent::onLand() {
    std::cout << "ты на клетке";
}
