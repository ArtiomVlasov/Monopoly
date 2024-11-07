#include "cell.hpp"
#include "player.hpp"
#include <functional>

class Tax : public Cell
{
private:
    const int tax;

public:
    void onLand() override;
    Tax(CellType type, const int tax);
    int getTaxAmount() const;
    void defaultAction(Player &player) override;
    ~Tax();
};

class Prison : public Cell
{
private:
    const int callDown;
    const int jailFee;

public:
    Prison(CellType type);
    void onLand() override;
    void defaultAction(Player &player) override; // отправить в тюрьму
    ~Prison();
};

class Chance : public Cell
{
private:
    std::vector<std::function<void(Player &)>> effects;
    void initializeEffects();

public:
    Chance(CellType type);
    void defaultAction(Player &player) override;
};
