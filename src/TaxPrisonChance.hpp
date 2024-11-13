#include "cell.hpp"
#include <functional>
#include "game.hpp"

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
    const int jailFee;

public:
    Prison();
    void onLand() override;
    void defaultAction(Player *player, Game* game) override; // отправить в тюрьму
    int getJailFee() const;
    void payToExit(Player* player);
    ~Prison();
};

class Chance : public Cell
{
private:
    std::vector<std::function<void(Player *)>> effects;
    void initializeEffects();

public:
    Chance(CellType type);
    void defaultAction(Player *player, Game* game) override;
};
