#pragma once

class Player;

class Game;

enum class CellType { // надо подумать можно ли как-то еще это реализовать
    RedStreet,
    YellowStreet,
    GreenStreet,
    BlueStreet,
    BrownStreet,
    WhiteStreet,
    PinkStreet,
    OrangeStreet,
    PropRailway,
    PropUtilities,
    Chance,
    Tax,
    publicTreasury,
    Prison
};

class Cell
{
protected:
    CellType type;
public:
    Cell(CellType t);
    virtual void onLand(); // сообщает на какую клетку попал
    CellType getType() const;
    int handleCellType(CellType propertyType);
    virtual void defaultAction(Player *player, Game* game) = 0;
    virtual ~Cell() = default;
    bool isEmpty();
};
