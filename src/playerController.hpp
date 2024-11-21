#include "property.hpp"
#include "propertySubClasses.hpp"
#include "player.hpp"
#include "render.hpp"
#pragma once
class playerController{
public:

    void playerMakeMove(int steps, Player* player);
    static void playerPay(int amount, Player* player);
    static void playerReceive(int amount, Player* player);
    static void playerAddProperty(Property* property, Player* player);
    static Player::AffordStatus playerCanAfford(int amount, Player* player);
    static void playerDeclareBankruptcy(Player *creditor);
    void buy(Property *property); //добавить
    bool playerCanBuildOn(Property* property, Player* player) const;
    void playerBuildStructure(Street* street, Player* player);
    void playerDestroyStructure(Street* steet, Player* player);

    static int playerMakeDicision(Player* player);
    static void playerStartAuction(Property *property, const std::vector<Player *> &players, Player* player);
    void playerMortgageProperty(Property* property, Player* player);
    void playerUnmortgagedProperty(Property* property, Player* player);
    void playerMoveToNearestStation(Game* game, int posIndex, Player* player);
    //void playerReleaseFromJail();
    // void playerSendToJail();
};
