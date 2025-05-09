
#pragma once
class Player;

class Game;
enum class CellType { // надо подумать можно ли как-то еще это реализовать
    Street,
    PropRailway,
    PropUtilities,
    Chance,
    Tax,
    EmptyCell,
    publicTreasury,
    Prison
};

class CellContent
{
protected:
    CellType type;
public:
    CellContent(CellType t);
    virtual void onLand(); // сообщает на какую клетку попал
    CellType getType() const;
    //int handleCellType(CellType propertyType);
    //virtual void defaultAction(Player *player, Game* game) = 0;
    // virtual ~CellContent() = default;
};
