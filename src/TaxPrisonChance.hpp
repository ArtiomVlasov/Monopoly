#include "cell.hpp"
#include <functional>
#include "game.hpp"
#include <map>
#pragma once
class Tax : public Cell
{
private:
    const int tax;

public:
    void onLand() override;
    Tax(const int tax);
    int getTaxAmount() const;
    void defaultAction(Player *player, Game* game) override;
    ~Tax();
};

class Prison : public Cell
{
private:
    const int callDown;
    static const int jailFee = 100;
    std::map<Player *, uint8_t> playerPrisonList;
public:
    uint8_t getNumMovesInPrison(Player* player);
    int getCallDown();
    // void addPlayerInPrison(Player *player);
    std::map<Player *, uint8_t> getPrisonList();
    //void playerReleaseFromJail();
    //static bool isInJail(Player* player);
    Prison();
    void defaultAction(Player *player, Game* game) override;
    //bool playerInPrison(Player* player);
    void onLand() override; //FIXME хуй знает что с этим делать    void defaultAction(Player *player, Game* game) override; // отправить в тюрьму
    int getJailFee();
    //void payToExit(Player* player);
    ~Prison();
};

class Chance : public Cell
{
private:
    std::vector<std::function<void(Player *)>> effects;
    void initializeEffects();
    Game* game;

public:
    Chance(Game *game);
    //void initializeEffects(Game *game);
    void defaultAction(Player *player, Game* game) override;
};


class PublicTreasury : public Cell {
public:
    void onLand() override;
    void defaultAction(Player* player, Game* game) override; 
    PublicTreasury();

private:
    std::vector<std::function<void(Player*)>> actions;
    void initializeActions();
};  

class EmptyCell : public Cell{
public:
    EmptyCell();
    void onLand() override;
    void defaultAction(Player* player, Game* game) override; 
};
