#include "property.hpp"
#include "player.hpp"
#include <cmath>

Property::Property(CellType type, std::string Name, int Price, int Rent, Player *owner)
    : Cell(type), name(Name), price(Price), rent(Rent), owner(owner), isMortgage(false) {}

void Property::defaultAction(Player *player, Game *game)
{
    if (owner != nullptr)
    {
        if (player->getName() != owner->getName() && !isMortgage)
        {
            int rentAmount = calculateRent(player);

            switch (player->canAfford(rentAmount))
            {
            case Player::AffordStatus::CAN_AFFORD:
                std::cout << "Игрок " << player->getName() << " попал на имущество, принадлежащее " << owner->getName()
                          << ". Заплатите ренту в размере " << rentAmount << " монет.\n";
                payRent(player); // Выполняем оплату ренты
                break;

            case Player::AffordStatus::NEED_TO_SELL_PROPERTY:
                std::cout << "Игрок " << player->getName() << " попал на имущество, принадлежащее " << owner->getName()
                          << ", но недостаточно средств на балансе. Продайте часть имущества для оплаты ренты в размере "
                          << rentAmount << " монет.\n";
                // какой то метод из Game наверно надо взять, он будет давать игроку возмежность сделать выбор что продать
                break;

            case Player::AffordStatus::CANNOT_AFFORD:
                std::cout << "Игрок " << player->getName() << " не может позволить себе оплатить ренту. Объявляется банкротство.\n";
                player->declareBankruptcy(owner);
                return;
            }
        }
        else if (player->getName() != owner->getName() && isMortgage)
        {
            std::cout << "Игрок " << player->getName() << " попал на заложенное имущество. Рента не требуется.\n";
            return;
        }
    }
    else if (player->canAfford(price) == Player::AffordStatus::CANNOT_AFFORD)
    {
        std::cout << "У игрока " << player->getName() << " недостаточно средств для покупки. Имущество отправляется на аукцион.\n";
        player->startAuction(this, game->getListOfPlayers());
        return;
    }
    int ans = player->makeDecision();
    switch (ans)
    {
    case 0: // может купить
        std::cout << "Игрок " << player->getName() << " решил купить имущество за " << price << " монет.\n";
        player->buy(this);
        break;
    case 1: // аукцион
        std::cout << "Игрок " << player->getName() << " выставляет имущество на аукцион.\n";
        player->startAuction(this, game->getListOfPlayers());
        break;
    }
}

void Property::payRent(Player *player)
{
    int amount = calculateRent(player);
    std::cout << "Игрок " << player->getName() << " платит ренту в размере " << amount << " монет игроку " << owner->getName() << ".\n";
    player->pay(amount);
    owner->receive(amount);
}

void Property::setOwner(Player *newOwner)
{
    owner = newOwner;
}

bool Property::isMortgaged()
{
    return isMortgage;
}

void Property::markAsAvailable()
{
    isMortgage = false;
    owner = nullptr;
}

int Property::getRent() const
{
    return this->rent;
}

bool Property::isOwned()
{
    return !this->name.empty();
}

int Property::getPrice() const
{
    return this->price;
}

std::string Property::getName() const
{
    return name;
}

void Property::mortgage()
{
    this->isMortgage = true;
    this->owner->receive(calculateMortgage());
}

void Property::unMortgage(Player *player)
{
    if (!player->isInJail() && !player->isBankrupt() && player->getBalance() >= calculateUnMortgage())
    {
        player->pay(calculateUnMortgage());
        this->isMortgage = false;
    }
}

bool Property::isFullListOfProperty(Player *player, CellType type)
{
    int countQuantityProperty = 0;
    for (const Property *property : player->getProperties())
    {
        if (property->getType() == type)
        {
            countQuantityProperty++;
        }
    }
    return countQuantityProperty == handleCellType(type);
}

int Property::calculateMortgage()
{
    return rent / 2;
}
int Property::calculateUnMortgage()
{
    return (rent / 2 + rent * 0.1);
}

bool Property::isStreet()
{
    if (type == CellType::PropUtilities || type == CellType::PropRailway)
    {
        return false;
    }
    return true;
}

Player *Property::getOwner()
{
    return owner;
}
