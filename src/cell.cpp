#include <cell.hpp>

Cell::Cell(CellType type):type(type){}

CellType Cell::getType() const {
    return type;
}
