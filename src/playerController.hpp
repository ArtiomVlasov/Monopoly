#include "property.hpp"
#include "propertySubClasses.hpp"
#include "player.hpp"
#include "render.hpp"
#pragma once
class StreetController;
class PropertyController;

class playerController{
private: 
    Player *player;
public:
    enum AffordStatus
    {
        CAN_AFFORD,
        NEED_TO_SELL_PROPERTY,
        CANNOT_AFFORD
    };
    playerController(Player *player);
    static void playerMakeMove(int steps, Player *Iplayer); // FIXME хз статик не статик
    static void playerPay(int amount, Player *Iplayer);
    static void playerReceive(int amount, Player *Iplayer);
    static void playerAddProperty(Property* property, Player *Iplayer);
    static AffordStatus playerCanAfford(int amount, Player *Iplayer);
    static void playerDeclareBankruptcy(Player *creditor, Player *Iplayer);
    static void playerBuy(Property *property, Player *Iplayer); //добавить
    bool playerCanBuildOn(Property* property, StreetController *streetCntl) const;
    void playerBuildStructure(Street* street, StreetController *streetCntl);
    void playerDestroyStructure(Street* street, StreetController *streetCntl);
    static int getOwnedPropertyCount(CellType type, Player *player);
    static int playerMakeDicision(Player *Iplayer);
    static void playerStartAuction(Property *property, const std::vector<Player *> &players, Player *Iplayer);
    void playerMortgageProperty(Property* property, PropertyController *propCntl);
    void playerUnmortgagedProperty(Property* property, PropertyController *propCntl);
    void playerMoveToNearestStation(Game* game, int posIndex);
    static int playerMakeBid(int currentHighestBid, Player *player);
    //void playerReleaseFromJail();
    // void playerSendToJail();
};
