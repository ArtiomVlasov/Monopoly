#include "player.hpp"

enum class CellType { Property, Chance, Tax, Prison, Street, Railway, Utilities};

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
