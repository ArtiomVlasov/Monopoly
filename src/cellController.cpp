#include "cellController.hpp"
#include "cellContent.hpp"
#include <iostream>

ArgsForDefAct *CellController::getArgs(Player *player, Game *game, playerController *plrCntl)
{
    ArgsForDefAct *args;
    
    if (cell->getType() == CellType::Street || cell->getType() == CellType::PropRailway || cell->getType() == CellType::PropUtilities)
    {
        std::cout<<"0000_______0000\n";
        args->player = player;
        std::cout<<"0000___+___0000\n";
        args->game = game;
        args->plrCntl = plrCntl;
    }
    std::cout<<"0000000000\n";
     if(cell->getType() == CellType::Chance || cell->getType() == CellType::publicTreasury || cell->getType() == CellType::Prison){
        args -> player = player;
    }
    else if(cell->getType() == CellType::Tax){
        args->player = player;
        args->game = game;
        args->plrCntl = plrCntl;
        // args->propCntl= propCntl;
    }
    
    return args;
}

CellController::CellController(CellContent *cell):cell(cell){}