#include "cell.hpp"
#include <iostream>
Cell::Cell(CellType type):type(type){}

CellType Cell::getType() const {
    return type;
}

void Cell::onLand() {
    std::cout << "ты на клетке";
}
