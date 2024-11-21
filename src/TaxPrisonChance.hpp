#include "cell.hpp"
#include <functional>
#include "game.hpp"
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
    std::vector<Player *> playerPrisonList;
public:
    Prison();
    bool playerInPrison(Player* player);
    void onLand() override;
    void defaultAction(Player *player, Game* game) override; // отправить в тюрьму
    static int getJailFee();
    void payToExit(Player* player);
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
    void initializeEffects(Game *game);
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
