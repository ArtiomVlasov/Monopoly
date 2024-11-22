#include "property.hpp"
#include "player.hpp"
#include "playerController.hpp"
#include "TaxPrisonChance.hpp"
#include "propertyController.hpp"
#include <cmath>


Property::Property(CellType type, std::string Name, int Price, int Rent, Player *owner)
    : Cell(type), name(Name), price(Price), rent(Rent), owner(owner), isMortgage(false) {}

void Property::defaultAction(Player *player, Game *game)
{
    if (owner != nullptr)
    {
        if (player->getName() != owner->getName() && !isMortgage)
        {
            int rentAmount = getTotalRent(player);

            switch (playerController::playerCanAfford(rentAmount, player))
            {
            case playerController::AffordStatus::CAN_AFFORD:
                std::cout << "Игрок " << player->getName() << " попал на имущество, принадлежащее " << owner->getName()
                          << ". Заплатите ренту в размере " << rentAmount << " монет.\n";
                PropertyController::payRent(player, this); // Выполняем оплату ренты
                break;

            case playerController::AffordStatus::NEED_TO_SELL_PROPERTY:
                std::cout << "Игрок " << player->getName() << " попал на имущество, принадлежащее " << owner->getName()
                          << ", но недостаточно средств на балансе. Продайте часть имущества для оплаты ренты в размере "
                          << rentAmount << " монет.\n";
                // какой то метод из Game наверно надо взять, он будет давать игроку возмежность сделать выбор что продать
                break;

            case playerController::AffordStatus::CANNOT_AFFORD:
                std::cout << "Игрок " << player->getName() << " не может позволить себе оплатить ренту. Объявляется банкротство.\n";
                playerController::playerDeclareBankruptcy(owner, player);
                return;
            }
        }
        else if (player->getName() != owner->getName() && isMortgage)
        {
            std::cout << "Игрок " << player->getName() << " попал на заложенное имущество. Рента не требуется.\n";
            return;
        }
    }
    else if (playerController::playerCanAfford(price, player) == playerController::AffordStatus::CANNOT_AFFORD)
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств для покупки. Имущество отправляется на аукцион.\n";
        playerController::playerStartAuction(this, game->getListOfPlayers(), player);
        return;
    }
    else
    {
        int ans = playerController::playerMakeDicision(player);
        switch (ans)
        {
        case 0: // может купить
            std::cout << "Игрок " << player->getName() << " решил купить имущество за " << price << " монет.\n";
            playerController::playerBuy(this, player);
            break;
        case 1: // аукцион
            std::cout << "Игрок " << player->getName() << " выставляет имущество на аукцион.\n";
            playerController::playerStartAuction(this, game->getListOfPlayers(), player);
            break;
        }
    }
}

/*void Property::payRent(Player *player)
{
    int amount = calculateRent(player);
    std::cout << "Игрок " << player->getName() << " платит ренту в размере " << amount << " монет игроку " << owner->getName() << ".\n";
    playerController::playerPay(amount, player);
    playerController::playerReceive(amount, player);
}*/

void Property::setOwner(Player *newOwner)
{
    owner = newOwner;
}

bool Property::isMortgaged()
{
    return isMortgage;
}

void Property::setMortgageStatus(bool status){
    isMortgage= status;
}

int Property::getRent() const
{
    return this->rent;
}

/*bool Property::isOwned()
{
    return !this->name.empty();
}*/

int Property::getPrice() const
{
    return this->price;
}

std::string Property::getName() const
{
    return name;
}

/*void Property::mortgage()
{
    this->isMortgage = true;
    playerController::playerReceive(calculateMortgage(), this->owner);
}

void Property::unMortgage(Player *player)
{
    if (!Prison::isInJail(player) && !Game::isBankruptPlayer(player) && player->getBalance() >= calculateUnMortgage())
    {
        playerController::playerPay(calculateUnMortgage(), player);
        this->isMortgage = false;
    }
}*/



/*int Property::calculateMortgage()
{
    return rent / 2;
}
int Property::calculateUnMortgage()
{
    return (rent / 2 + rent * 0.1);
}*/

Player *Property::getOwner()
{
    return owner;
}
