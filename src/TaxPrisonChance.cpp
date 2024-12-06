#include "TaxPrisonChance.hpp"
#include "player.hpp"
#include "playerController.hpp"
#include "TaxPrisonChanceCntl.hpp"
#include "render.hpp"
#include <iostream>

Tax::Tax(const int tax) : CellContent(CellType::Tax), tax(tax) {}

void Tax::onLand()
{
    std::cout << "Вы попали на налоговую ячейку. С вас взимается налог." << std::endl;
}

int Tax::getTaxAmount() const
{
    return tax;
}

Tax::~Tax() {}

std::map<Player *, uint8_t> *Prison::getPlayerPrisonList()
{
    if (playerPrisonList->empty()){
        return nullptr;
    }
    return playerPrisonList;
}

uint8_t Prison::getNumMovesInPrison(Player *player)
{
    auto it = playerPrisonList->find(player);

    return it->second;
}

int Prison::getCallDown()
{
    return callDown;
}

Prison::Prison() : CellContent(CellType::Prison), callDown(3), playerPrisonList(new std::map<Player *, uint8_t>()) {}

void Prison::onLand()
{
    std::cout << "Вы попали в тюрьму. Пропускаете ходы." << std::endl;
}

int Prison::getJailFee()
{
    return jailFee;
}

// void Prison::payToExit(Player *player)
// {
//     if (playerController::playerCanAfford(jailFee, player) == Player::AffordStatus::CAN_AFFORD)
//     {
//         std::cout << "Игрок " << player->getName() << " заплатил " << jailFee << " монет для выхода из тюрьмы." << std::endl;
//         playerController::playerPay(jailFee);
//         preleaseFromJail();
//     }
//     else
//     {
//         std::cout << "У игрока " << player->getName() << " недостаточно средств, чтобы выйти из тюрьмы." << std::endl;
//     }
// }

Prison::~Prison() {}

// Chance class implementation
Chance::Chance() : CellContent(CellType::Chance)
{
    initializeEffects();
}

std::vector<std::function<void(Player *)>> Chance::getEffectsList()
{
    return effects;
}

void Chance::initializeEffects()
{
    effects = {
        // Перемещение на ближайшую станцию
        [](Player *player)
        {
            std::cout << player->getName() << " перемещается на ближайшую станцию.\n";
            playerController::playerMoveToNearestStation(player);
        },
        // Премия за победу в конкурсе
        [](Player *player)
        {
            int prize = 200;
            std::cout << player->getName() << " получает " << prize << " монет за победу в конкурсе красоты.\n";
            renderReceivePlayer(player, prize);
            player->setBalance(player->getBalance() + prize);
            // playerController::playerReceive(prize, player);
        },
        // Оплата налога
        [](Player *player)
        {
            int tax = 100;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            renderPayPlayer(player, tax);
            player->setBalance(player->getBalance() - tax);
            // playerController::playerPay(tax, player);
        },
        // Плата за ремонт построек
        [](Player *player)
        {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            renderPayPlayer(player, totalFee);
            player->setBalance(player->getBalance() - totalFee);
            // playerController::playerPay(totalFee, player);
        },
        [](Player *player)
        {
            std::cout << player->getName() << " перемещается на старт и получает 200 монет.\n";
            player->setPosition(0);
            renderReceivePlayer(player, 200);
            player->setBalance(player->getBalance() + 200);
            // playerController::playerReceive(200, player);
        }};
}

PublicTreasury::PublicTreasury() : CellContent(CellType::publicTreasury)
{
    initializeActions();
}

void PublicTreasury::onLand()
{
    std::cout << "Вы попали на 'Общественную казну'!\n";
}

void PublicTreasury::initializeActions()
{
    actions = {
        [](Player *player)
        {
            int amount = 100;
            std::cout << player->getName() << " получает " << amount << " монет из Общественной казны.\n";
            renderReceivePlayer(player, amount);
            player->setBalance(player->getBalance() + amount);
            // playerController::playerReceive(amount, player);
        },

        [](Player *player)
        {
            int tax = 50;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            renderPayPlayer(player, tax);
            player->setBalance(player->getBalance() - tax);
            // playerController::playerPay(tax, player);
        },

        [](Player *player)
        {
            int steps = 3;
            std::cout << player->getName() << " продвигается на " << steps << " клетки вперёд.\n";
            player->setPosition(player->getPosition() + steps);
            // playerController::playerMakeMove(steps, player); //FIXME перенести к контроллер?
        },

        [](Player *player)
        {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            renderPayPlayer(player, totalFee);
            player->setBalance(player->getBalance() - totalFee);
            // playerController::playerPay(totalFee, player);
        },

        [](Player *player)
        {
            int reward = 200;
            std::cout << player->getName() << " получает награду в размере " << reward << " монет.\n";
            renderReceivePlayer(player, reward);
            player->setBalance(player->getBalance() + reward);
            // playerController::playerReceive(reward, player);
        },

        [](Player *player)
        {
            int refund = 20;
            std::cout << player->getName() << " получает возврат налогов в размере " << refund << " монет.\n";
            renderReceivePlayer(player, refund);
            player->setBalance(player->getBalance() + refund);
            // playerController::playerReceive(refund, player);
        }};
}

std::vector<std::function<void(Player *)>> PublicTreasury::getEffectsList()
{
    return actions;
}

EmptyCell::EmptyCell() : CellContent(CellType::EmptyCell) {}

void EmptyCell::onLand()
{
    std::cout << "Вы попали на 'Бесплатную парковку', можете передохнуть!\n";
}
