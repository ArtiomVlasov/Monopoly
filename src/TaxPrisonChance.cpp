#include <TaxPrisonChance.hpp>
#include <iostream>

Tax::Tax(const int tax) : Cell(CellType::Tax), tax(tax) {}

void Tax::onLand()
{
    std::cout << " You have stepped on the tax square. You must pay tax to the treasury " << std::endl;
}

void Tax::defaultAction(Player &player, Game& game)
{
    if (player.canAfford(tax))
    {
        player.pay(tax);
        std::cout << player.getName() << " Paid tax in the amount " << tax << " M " << std::endl;
    }
    else
    {
        std::cout << player.getName() << " cannot afford the tax and will go bankrupt." << std::endl;
        player.declareBankruptcy(); //
    }
}

int Tax::getTaxAmount() const
{
    return tax;
}

Prison::Prison() : Cell(CellType::Prison), callDown(3), jailFee(/*???*/) {}

void Prison::onLand()
{
    std::cout << " ......... " << callDown << " ......." << std::endl;
}

void Prison::defaultAction(Player &player, Game& game)
{
    player.sendToJail();
    std::cout << player.getName() << " .......... " << std::endl;
}

int Prison::getJailFee() const
{
    return jailFee;
}

void Prison::payToExit(Player &player)
{
    if (player.canAfford(jailFee))
    {
        player.pay(jailFee);
        player.releaseFromJail();
        std::cout << player.getName() << " paid jail fee and was released from prison. " << std::endl;
    }
    else
    {
        std::cout << player.getName() << " can't afford the fine to get out of jail." << std::endl;
    }
}

