#include "propertyController.hpp"
#include "playerController.hpp"
#include "TaxPrisonChance.hpp"
#include "TaxPrisonChanceCntl.hpp"
#include "render.hpp"

PropertyController::PropertyController(Property *property) :CellController(property) {
    this -> property = property;
}

void PropertyController::defaultAction(ArgsForDefAct *args)
{
    if (property->getOwner() != nullptr)
    {
        if (args->player->getName() != property->getOwner()->getName() && !property->isMortgaged())
        {
            int rentAmount = getTotalRent(args);

            switch (args->plrCntl->playerCanAfford(rentAmount))
            {
            case playerController::AffordStatus::CAN_AFFORD:
                std::cout << "Игрок " << args->player->getName() << " попал на имущество, принадлежащее " << property->getOwner()->getName()
                          << ". Заплатите ренту в размере " << rentAmount << " монет.\n";
                payRent(args); // Выполняем оплату ренты
                break;

            case playerController::AffordStatus::NEED_TO_SELL_PROPERTY:
                std::cout << "Игрок " << args->player->getName() << " попал на имущество, принадлежащее " << property->getOwner()->getName()
                          << ", но недостаточно средств на балансе. Продайте часть имущества для оплаты ренты в размере " //FIXME убрать весь текст в render
                          << rentAmount << " монет.\n";
                // какой то метод из Game наверно надо взять, он будет давать игроку возмежность сделать выбор что продать
                break;

            case playerController::AffordStatus::CANNOT_AFFORD:
                std::cout << "Игрок " << args->player->getName() << " не может позволить себе оплатить ренту. Объявляется банкротство.\n";
                args->plrCntl->playerDeclareBankruptcy(property->getOwner(), args->game);
                return;
            }
        }
        else if (args->player->getName() != property->getOwner()->getName() &&  !property->isMortgaged())
        {
            std::cout << "Игрок " << args->player->getName() << " попал на заложенное имущество. Рента не требуется.\n";
            return;
        }
    }
    else if (args ->plrCntl->playerCanAfford(property-> getPrice()) == playerController::AffordStatus::CANNOT_AFFORD)
    {
        std::cout << "У игрока " << args->player->getName() << " недостаточно средств для покупки. Имущество отправляется на аукцион.\n";
        args->plrCntl->playerStartAuction(property, args->game->getListOfPlayers(), this);
        return;
    }
    else
    {
        int ans = args->plrCntl->playerMakeDicision();
        switch (ans)
        {
        case 0: // может купить
            std::cout << "Игрок " << args->player->getName() << " решил купить имущество за " << property->getPrice() << " монет.\n";
            args->plrCntl->playerBuy(property);
            break;
        case 1: // аукцион
            std::cout << "Игрок " << args->player->getName() << " выставляет имущество на аукцион.\n";
            args->plrCntl->playerStartAuction(property, args->game->getListOfPlayers(), this);
            break;
        }
    }
}

void PropertyController::payRent(ArgsForDefAct *args)
{
    int amount = getTotalRent(args);
    renderPayPlater(args->player, amount, property);
    renderPayPlayer(args->player, amount);
    args->player->setBalance(args->player->getBalance() - amount);
    // playerController::playerPay(amount, player);
    renderReceivePlayer(args->player, amount);
    property->getOwner()->setBalance(args->player->getBalance() + amount);
    // playerController::playerReceive(amount, property -> getOwner());
}

void PropertyController::mortgageProperty(Player *player)
{
    property->setMortgageStatus(true);
    renderReceivePlayer(player, calculateMortgage());
    player->setBalance(player->getBalance() + calculateMortgage());
    // playerController::playerReceive(calculateMortgage(property), property->getOwner());
}

void PropertyController::markAsAvailable(Property *property)
{
    property->setMortgageStatus(false);
    property->setOwner(nullptr);
}

void PropertyController::unMortgageProperty(Player *player)
{
    int amount = calculateUnMortgage();
    if (player->getBalance() >= amount)
    {
        renderPayPlayer(player, amount);
        player->setBalance(player->getBalance() - amount);
        // playerController::playerPay(calculateUnMortgage(), player);
        property->setMortgageStatus(false);
    }
}

bool PropertyController::isOwnedProperty()
{
    if (property->getOwner())
    {
        return true;
    }
    return false;
}

int PropertyController::calculateMortgage()
{
    return property->getRent() / 2;
}

int PropertyController::calculateUnMortgage()
{
    return (property->getRent() / 2 + property->getRent() * 0.1);
}


