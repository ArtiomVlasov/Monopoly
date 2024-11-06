#include "cell.hpp"
#include "player.hpp"
#include <functional>

class Tax : public Cell
{
private:
    const int tax;

public:
    void onLand() override;
    Tax(const int tax);
    int getTaxAmount() const;
    void applyEffect(Player &player) override;
    ~Tax();
};

class Prison : Cell
{
private:
    const int callDowm;
    const int jailFee;

public:
    Prison();
    void onLand() override;
    void applyEffect(Player &player) override; // отправить в тюрьму
    ~Prison();
};

class Chance : public Cell
{
public:
    Chance();
    void applyEffect(Player &player) override;

private:
    std::vector<std::function<void(Player &)>> effects; 
    void initializeEffects();                           
};
