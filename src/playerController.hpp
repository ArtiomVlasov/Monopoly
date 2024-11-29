#pragma once
#include "property.hpp"
#include "propertySubClasses.hpp"
#include "player.hpp"

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
    // static void playerSellProperty(Player* player, Property* property);
    // static void playerMakeMove(int steps, Player *Iplayer);
    // static void playerPay(int amount, Player *Iplayer);
    // static void playerReceive(int amount, Player *Iplayer);
    // static void playerAddProperty(Property* property, Player *Iplayer);
     AffordStatus playerCanAfford(int amount);
     void playerDeclareBankruptcy(Player *creditor, Game *game);
     void playerBuy(Property *property); //добавить
    bool playerCanBuildOn(Property* property, StreetController *strCntl) const;
    void playerBuildStructure(Street* street, StreetController *streetCntl);
    void playerDestroyStructure(Street* street, StreetController *streetCntl);
     int getOwnedPropertyCount(CellType type);
     int playerMakeDicision();
     void playerStartAuction(Property *property, const std::vector<Player *> &players, PropertyController *propCntl);
    void playerMortgageProperty(Property* property);
    void playerUnmortgagedProperty(Property* property, PropertyController *propCntl);
    static void playerMoveToNearestStation(Player *player);
     int playerMakeBid(int currentHighestBid, PropertyController *propCntl);
     int getTotalPriceOfProperty();
    //void playerReleaseFromJail();
    // void playerSendToJail();
};
