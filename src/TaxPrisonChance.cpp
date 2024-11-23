#include "TaxPrisonChance.hpp"
#include "player.hpp"
#include "playerController.hpp"
#include "prisonController.hpp"
#include <iostream>

Tax::Tax(const int tax) : Cell(CellType::Tax), tax(tax) {}

void Tax::onLand()
{
    std::cout << "Вы попали на налоговую ячейку. С вас взимается налог." << std::endl;
}

int Tax::getTaxAmount() const
{
    return tax;
}

void Tax::defaultAction(Player *player, Game *game)
{
    std::cout << "Игрок " << player->getName() << " должен заплатить налог в размере " << tax << " монет." << std::endl;
    playerController::AffordStatus affordStatus = playerController::playerCanAfford(tax, player);
    if (affordStatus == playerController::AffordStatus::CAN_AFFORD)
    {
        playerController::playerPay(tax, player);
    }
    else if (affordStatus == playerController::AffordStatus::NEED_TO_SELL_PROPERTY)
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств на балансе. " << "Необходимо продать имущество для оплаты налога.\n";

        while (playerController::playerCanAfford(tax, player) == playerController::AffordStatus::NEED_TO_SELL_PROPERTY)
        {
            game->sellProperty(player); //??????????????????
        }
    }
    else
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств для уплаты налога." << std::endl;
        Game::addBankruptPlayers(nullptr);
    }
}

Tax::~Tax() {}

Prison::Prison() : Cell(CellType::Prison), callDown(3) {}

void Prison::onLand()
{
    std::cout << "Вы попали в тюрьму. Пропускаете ходы." << std::endl;
}

void Prison::defaultAction(Player *player, Game *game)
{
    std::cout << "Игрок " << player->getName() << " отправляется в тюрьму." << std::endl;
    prisonController::addPlayerInPrison(player);
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
Chance::Chance(Game *game) : Cell(CellType::Chance), game(game)
{
    initializeEffects();
}

void Chance::initializeEffects()
{
    effects = {
        // Перемещение на ближайшую станцию
        [this](Player *player)
        {
            std::cout << player->getName() << " перемещается на ближайшую станцию.\n";
            if (player->getPosition() == 7) {
                playerController::playerMoveToNearestStation(this->game, 7, player);
            }
            else if (player->getPosition() == 23)   {
                playerController::playerMoveToNearestStation(this->game, 23, player);
            } 
            else if (player->getPosition() == 36) {
                 playerController::playerMoveToNearestStation(this->game, 36, player); // FIXME тоже чё то надо думать
            }
        },
        // Премия за победу в конкурсе
        [](Player *player)
        {
            int prize = 200;
            std::cout << player->getName() << " получает " << prize << " монет за победу в конкурсе красоты.\n";
            playerController::playerReceive(prize, player);
        },
        // Оплата налога
        [](Player *player)
        {
            int tax = 100;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            playerController::playerPay(tax, player);
        },
        // Отправка в тюрьму
        [](Player *player)
        {
            std::cout << player->getName() << " отправляется в тюрьму.\n";
            prisonController::addPlayerInPrison(player);
        },
        // Плата за ремонт построек
        [](Player *player)
        {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            playerController::playerPay(totalFee, player);
        },
        [](Player *player)
        {
            std::cout << player->getName() << " перемещается на старт и получает 200 монет.\n";
            player->setPosition(0);
            playerController::playerReceive(200, player);
        }};
}

void Chance::defaultAction(Player *player, Game *game)
{
    std::cout << "Игрок " << player->getName() << " вытягивает карту 'Шанс'." << std::endl;
    int effectIndex = rand() % effects.size();
    effects[effectIndex](player);
}

PublicTreasury::PublicTreasury() : Cell(CellType::publicTreasury) {
        initializeActions();
    }

void PublicTreasury::onLand() {
    std::cout << "Вы попали на 'Общественную казну'!\n";
}

void PublicTreasury::initializeActions() {
    actions = {
        [](Player* player) {
            int amount = 100;
            std::cout << player->getName() << " получает " << amount << " монет из Общественной казны.\n";
            playerController::playerReceive(amount, player);
        },
        
        [](Player* player) {
            int tax = 50;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            playerController::playerPay(tax, player);
        },
        
        [](Player* player) {
            int steps = 3;
            std::cout << player->getName() << " продвигается на " << steps << " клетки вперёд.\n";
            playerController::playerMakeMove(steps, player); //FIXME перенести к контроллер?
        },
        
        [](Player* player) {
            std::cout << player->getName() << " отправляется в тюрьму.\n";
            prisonController::addPlayerInPrison(player);//FIXME бля походу надо либо класс Prison делать статиком либо надо дуумать 
        },
        
        [](Player* player) {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            playerController::playerPay(totalFee, player);
        },
        
        [](Player* player) {
            int reward = 200;
            std::cout << player->getName() << " получает награду в размере " << reward << " монет.\n";
            playerController::playerReceive(reward, player);
        },
        
        [](Player* player) {
            int refund = 20;
            std::cout << player->getName() << " получает возврат налогов в размере " << refund << " монет.\n";
            playerController::playerReceive(refund, player);
        }
    };
}

void PublicTreasury::defaultAction(Player* player, Game* game) {
    int effectIndex = rand() % actions.size();
    std::cout << player->getName() << " попадает на клетку 'Общественная казна'.\n";
    actions[effectIndex](player);
}

EmptyCell::EmptyCell(): Cell(CellType::EmptyCell){}

void EmptyCell::onLand() {
    std::cout << "Вы попали на 'Бесплатную парковку', можете передохнуть!\n";
}
void EmptyCell::defaultAction(Player* player, Game* game){} 
