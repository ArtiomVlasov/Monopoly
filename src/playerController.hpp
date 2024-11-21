#include "property.hpp"
#include "propertySubClasses.hpp"
#include "player.hpp"
#include "render.hpp"
#pragma once
class playerController{
public:

    void playerMakeMove(int steps, Player* player);
    void playerPay(int amount, Player* player);
    void playerReceive(int amount, Player* player);
    void playerAddProperty(Property* property, Player* player);
    void playerCanAfford(int amount, Player* player);
    void playerDeclareBankruptcy(Player *creditor);
    bool playerCanBuildOn(Property* property, Player* player) const;
    void playerBuildStructure(Street* street, Player* player);
    void playerDestroyStructure(Street* steet, Player* player);
    int playerMakeBid(int currentHighestBid, Player *player);
    int playerMakeDicision();
    void playerStartAuction();
    void playerMortgageProperty(Property* property);
    void playerUnmortgagedProperty(Property* property);
    void playerMoveToNearestStation(Game* game, int posIndex);
    void playerReleaseFromJail();
    // void playerSendToJail();
};
