#include "cellController.hpp"
#include "cellContent.hpp"
#include <iostream>

ArgsForDefAct *CellController::getArgs(Player *player, Game *game, playerController *plrCntl)
{
    ArgsForDefAct *args = new ArgsForDefAct();
    args->player = nullptr;
    args->game = nullptr;
    args->plrCntl = nullptr;
    if (cell->getType() == CellType::Street || cell->getType() == CellType::PropRailway || cell->getType() == CellType::PropUtilities)
    {
        args->player = player;
        args->game = game;
        args->plrCntl = plrCntl;
    }
    else if (cell->getType() == CellType::Chance || cell->getType() == CellType::publicTreasury || cell->getType() == CellType::Prison)
    {
        args->player = player;
        
    }
    else if (cell->getType() == CellType::Tax)
    {
        args->player = player;
        args->game = game;
        args->plrCntl = plrCntl;
        
        // args->propCntl= propCntl;
    }
    return args;
    
}

CellController::CellController(CellContent *cell) : cell(cell) {
}