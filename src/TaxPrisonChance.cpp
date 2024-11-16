#include "TaxPrisonChance.hpp"
#include "player.hpp"
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
    Player::AffordStatus affordStatus = player->canAfford(tax);
    if (affordStatus == Player::AffordStatus::CAN_AFFORD)
    {
        player->pay(tax);
    }
    else if (affordStatus == Player::AffordStatus::NEED_TO_SELL_PROPERTY)
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств на балансе. " << "Необходимо продать имущество для оплаты налога.\n";

        while (player->canAfford(tax) == Player::AffordStatus::NEED_TO_SELL_PROPERTY)
        {
            game->sellProperty(player); //??????????????????
        }
    }
    else
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств для уплаты налога." << std::endl;
        player->declareBankruptcy(nullptr);
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
    player->sendToJail();
}

int Prison::getJailFee()
{
    return jailFee;
}

void Prison::payToExit(Player *player)
{
    if (player->canAfford(jailFee) == Player::AffordStatus::CAN_AFFORD)
    {
        std::cout << "Игрок " << player->getName() << " заплатил " << jailFee << " монет для выхода из тюрьмы." << std::endl;
        player->pay(jailFee);
        player->releaseFromJail();
    }
    else
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств, чтобы выйти из тюрьмы." << std::endl;
    }
}

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
                player->moveToNearestStation(this->game, 7);
            }
            else if (player->getPosition() == 23)   {
                player->moveToNearestStation(this->game, 23);
            } 
            else if (player->getPosition() == 36) {
                 player->moveToNearestStation(this->game, 36);
            }
        },
        // Премия за победу в конкурсе
        [](Player *player)
        {
            int prize = 200;
            std::cout << player->getName() << " получает " << prize << " монет за победу в конкурсе красоты.\n";
            player->receive(prize);
        },
        // Оплата налога
        [](Player *player)
        {
            int tax = 100;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            player->pay(tax);
        },
        // Отправка в тюрьму
        [](Player *player)
        {
            std::cout << player->getName() << " отправляется в тюрьму.\n";
            player->sendToJail();
        },
        // Плата за ремонт построек
        [](Player *player)
        {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            player->pay(totalFee);
        },
        [](Player *player)
        {
            std::cout << player->getName() << " перемещается на старт и получает 200 монет.\n";
            player->setPosition(0);
            player->receive(200);
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
            player->receive(amount);
        },
        
        [](Player* player) {
            int tax = 50;
            std::cout << player->getName() << " должен заплатить налог в размере " << tax << " монет.\n";
            player->pay(tax);
        },
        
        [](Player* player) {
            int steps = 3;
            std::cout << player->getName() << " продвигается на " << steps << " клетки вперёд.\n";
            player->makeMove(steps);
        },
        
        [](Player* player) {
            std::cout << player->getName() << " отправляется в тюрьму.\n";
            player->sendToJail();
        },
        
        [](Player* player) {
            int houseFee = 40;
            int hotelFee = 115;
            int totalFee = player->getNumberOfHouses() * houseFee + player->getNumberOfHotels() * hotelFee;
            std::cout << player->getName() << " платит " << totalFee << " монет за ремонт построек.\n";
            player->pay(totalFee);
        },
        
        [](Player* player) {
            int reward = 200;
            std::cout << player->getName() << " получает награду в размере " << reward << " монет.\n";
            player->receive(reward);
        },
        
        [](Player* player) {
            int refund = 20;
            std::cout << player->getName() << " получает возврат налогов в размере " << refund << " монет.\n";
            player->receive(refund);
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