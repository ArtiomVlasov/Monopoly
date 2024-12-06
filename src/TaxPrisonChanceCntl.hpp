#pragma once
#include "TaxPrisonChance.hpp"
#include "cellController.hpp"

class prisonController : public CellController
{
private:
    Prison *prison;

public:
    prisonController(Prison *prison);
    void playerReleaseFromJail(Player *player);
    bool isInJail(Player *player);
    void payToExit(Player *player, playerController *plrCntl);
    void addPlayerInPrison(Player *player);
    Prison *getPrison();
    void defaultAction(ArgsForDefAct *args) override;
};

class TaxController : public CellController
{
private:
    Tax *tax;
public:
    TaxController(Tax *tax);
    void defaultAction(ArgsForDefAct *args) override;
};

class ChanceController : public CellController
{
private:
    Chance *chance;
public:
    ChanceController(Chance *chance);
    
    void defaultAction(ArgsForDefAct *args) override;
};


class PublicTreasuryController : public CellController {
private:
    PublicTreasury *treasure;
public:

    void defaultAction(ArgsForDefAct *args) override; 
    PublicTreasuryController(PublicTreasury *treasure);
};  

class EmptyCellController : public CellController{
private:
    EmptyCell* emptyCell;
public:
    EmptyCellController(EmptyCell* emptyCell);

    void defaultAction(ArgsForDefAct *args) override; 
};