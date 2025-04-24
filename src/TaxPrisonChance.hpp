#pragma once
#include "cellContent.hpp"
#include <functional>
#include "game.hpp"
#include <map>

class Tax : public CellContent
{
private:
    const int tax;

public:
    void onLand() override;
    Tax(const int tax);
    int getTaxAmount() const;
    // void defaultAction(Player *player, Game* game) override;
    ~Tax();
};

class Prison : public CellContent
{
private:
    const int callDown;
    static const int jailFee = 100;
    std::map<Player *, uint8_t> *playerPrisonList;
public:
    std::map<Player *, uint8_t> *getPlayerPrisonList();
    uint8_t getNumMovesInPrison(Player* player);
    int getCallDown();
    // void addPlayerInPrison(Player *player);
    //void playerReleaseFromJail();
    //static bool isInJail(Player* player);
    Prison();
    // void defaultAction(Player *player, Game* game) override;
    //bool playerInPrison(Player* player);
    void onLand() override; //FIXME хуй знает что с этим делать    void defaultAction(Player *player, Game* game) override; // отправить в тюрьму
    int getJailFee();
    //void payToExit(Player* player);
    ~Prison();
};

class Chance : public CellContent
{
private:
    std::vector<std::function<void(Player *)>> effects;
    void initializeEffects();
    

public:
    Chance();
    std::vector<std::function<void(Player *)>> getEffectsList();
    //void initializeEffects(Game *game);
    //void defaultAction(Player *player, Game *game) override;
};


class PublicTreasury : public CellContent {
public:
    void onLand() override;
    //void defaultAction(Player* player, Game* game) override; 
    PublicTreasury();
    std::vector<std::function<void(Player*)>> getEffectsList();

private:
    std::vector<std::function<void(Player*)>> actions;
    void initializeActions();
};  

class EmptyCell : public CellContent{
public:
    EmptyCell();
    void onLand() override;
    // void defaultAction(Player* player, Game* game) override; 
};
