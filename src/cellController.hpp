#pragma once
class CellContent;
class Player;
class Game;
class playerController;
class PropertyController;

typedef struct ArgsForDefAct{
    Player *player;
    Game *game;
    playerController *plrCntl;
    // PropertyController *propCntl = nullptr;
}ArgsForDefAct;

class CellController
{
private:
    CellContent* cell;
public:

    CellController(CellContent *cell);
    virtual void defaultAction(ArgsForDefAct *args) = 0;
    ArgsForDefAct *getArgs(Player *player, Game *game, playerController *plrCntl);
};
