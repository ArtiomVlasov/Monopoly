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
    Player::AffordStatus playerCanAfford(int amount, Player* player);
    void playerDeclareBankruptcy(Player *creditor);
    void buy(Property *property); //добавить
    bool playerCanBuildOn(Property* property, Player* player) const;
    void playerBuildStructure(Street* street, Player* player);
    void playerDestroyStructure(Street* steet, Player* player);
    int playerMakeBid(int currentHighestBid, Player *player);
    int playerMakeDicision(Player* player);
    void playerStartAuction(Property *property, const std::vector<Player *> &players, Player* player);
    void playerMortgageProperty(Property* property, Player* player);
    void playerUnmortgagedProperty(Property* property, Player* player);
    void playerMoveToNearestStation(Game* game, int posIndex, Player* player);
    //void playerReleaseFromJail();
    // void playerSendToJail();
};
