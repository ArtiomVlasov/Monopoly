#include "player.hpp"
#include "propertySubClasses.hpp"
#include "cell.hpp"

Player::Player(std::string name) : name(name), balance(2000), position(0), inJail(false), bankrupt(false), numMovesInPrison(0), listOfProperty() {}

int Player::getTotalPriceOfProperty()
{
    return totalPriceOfProperty;
}

void Player::makeMove(int steps)
{
    position = (position + steps) % 40; // не уверен что это так
}

void Player::pay(int amount)
{
    std::cout << "С баланса игрока " << name << " списано " << amount << " монет.\n";
    balance -= amount;
}

void Player::receive(int amount)
{
    std::cout << "Игрок " << name << " получает " << amount << " монет.\n";
    balance += amount;
}

void Player::addProperty(Property *property)
{
    totalPriceOfProperty += property->calculateMortgage();
    property->setOwner(this);
    listOfProperty.push_back(property);
}

Player::AffordStatus Player::canAfford(int amount)
{
    if (amount <= balance)
    {
        return CAN_AFFORD;
    }
    if (amount > balance + totalPriceOfProperty)
    {
        return CANNOT_AFFORD;
    }
    return NEED_TO_SELL_PROPERTY;
}

void Player::declareBankruptcy(Player *creditor)
{
    bankrupt = true;
    std::cout << "Игрок " << name << " не может оплатить ренту и объявляет банкротство.\n";
    if (creditor)
    {
        std::cout << "Его имущество переходит к " << creditor->getName() << ".\n";
        for (Property *property : listOfProperty)
        {
            creditor->addProperty(property);
            std::cout << property->getName() << " переходит к " << creditor->getName() << ".\n";
        }
        creditor->receive(balance);
    }
    else
    {
        for (Property *property : listOfProperty)
        {
            property->markAsAvailable();
        }
        std::cout << "Его имущество возвращается банку и снова доступно для покупки.\n";
    }
    listOfProperty.clear();
    balance = 0;
}

/*void Player::mortgageProperty(Property& property){
    if(property.)
}*/

int Player::getBalance() const
{
    return balance;
}

std::string Player::getName() const
{
    return name;
}

int Player::getPosition() const
{
    return position;
}

const std::vector<Property *> &Player::getProperties() const
{
    return listOfProperty;
}

bool Player::isBankrupt() const
{
    return bankrupt;
}

bool Player::isInJail() const
{
    return inJail;
}

void Player::sendToJail()
{
    position = 10;
    numMovesInPrison = 1;
    inJail = true;
}

void Player::releaseFromJail()
{
    inJail = false;
}

bool Player::canBuildOn(Property *property) const{
    Street *street = dynamic_cast<Street *>(property);
    if (!street) {
        std::cout << "Невозможно построить, так как это не улица.\n";
        return false;
    }

    if (street->getOwner() != this) {
        std::cout << "Улица не принадлежит игроку " << name << ".\n";
        return false;
    }
    if (!street->isFullListOfProperty(property -> getOwner(), street -> getType())) {
        std::cout << "Игрок должен владеть всей цветовой группой, чтобы строить здесь.\n";
        return false;
    }

    if (street->isMortgaged()) {
        std::cout << "Невозможно построить, пока улица заложена.\n";
        return false;
    }

    return true;
}

void Player::buildStructure(Street *street)
{
    if (canBuildOn(street) && balance >= street->getBuildingCost())
    {
        pay(street->getBuildingCost());
        street->buildNewHouse();

        std::cout << "Игрок " << name << " построил здание на \"" << street->getName() 
                  << "\". Уровень улицы теперь: " << street->getLevelOfStreet() << ".\n";
    }
    else if (balance < street->getBuildingCost())
    {
        std::cout << "Недостаточно средств для строительства на \"" << street->getName() << "\".\n";
    }
    
}

void Player::destroyStructure(Street *street) {
    if (street->getOwner() != this) { // хз надо здесь проверять это
        std::cout << "Игрок " << name << " не владеет этой улицей.\n";
        return;
    }

    if (street->getLevelOfStreet() == 1) {
        std::cout << "На улице " << street->getName() << " нет построек для сноса.\n";
        return;
    }

    // Снос здания
    street->demolishHouse();
    std::cout << "Игрок " << name << " снес одну структуру на " << street->getName() << ".\n";
}

void Player::incrementNumMovesInPrison()
{
    numMovesInPrison++;
}

int Player::getNumMovesInPrison()
{
    return numMovesInPrison;
}

int makeBid(int currentHighestBid, Player *player)
{
    std::cout << player->getName() << ", текущая наивысшая ставка: " << currentHighestBid << ". Введите вашу ставку или -1 для выхода: ";
    std::cout << "Наименьшая ставка 10М. \n";
    int bid;
    std::cin >> bid; // не знаю наверно верно
    if (bid < 0)
    {
        std::cout << player->getName() << " выходит из аукциона.\n";
        return -1;
    }

    if (bid > currentHighestBid && player->canAfford(bid) == Player::AffordStatus::CAN_AFFORD)
    {
        std::cout << player->getName() << " сделал ставку: " << bid << "\n";
        return bid;
    }
    else if (bid > currentHighestBid && player->canAfford(bid) == Player::AffordStatus::CANNOT_AFFORD)
    {
        if (player->getBalance() >= currentHighestBid + 10)
        {
            std::cout << player->getName() << ", Ваш балланс должен быть не меньше ставки которую вы хотите сделать. Снизьте ставку.\n";
            return makeBid(currentHighestBid, player);
        }
        else
        {
            std::cout << "У" << player->getName() << ", не хватает денег, он выходит из аукциона. \n";
            return -1;
        }
    }
    else
    {
        std::cout << player->getName() << ", Ставка должна быть выше текущей наивысшей ставки.\n";
        return makeBid(currentHighestBid, player);
    }
}

int Player::makeDecision()
{
    int decision;
    std::cout << "Игрок " << name << ", вы попали на недвижимость.\n";
    std::cout << "Выберите действие:\n";
    std::cout << "0 - Купить недвижимость\n";
    std::cout << "1 - Начать аукцион\n";
    std::cout << "Введите ваш выбор: ";

    std::cin >> decision;

    while (decision < 0 || decision > 2)
    {
        std::cout << "Неверный выбор. Пожалуйста, введите 0, 1 или 2: ";
        std::cin >> decision;
    }

    return decision;
}

void Player::startAuction(Property *property, const std::vector<Player *> &players)
{
    int highestBid = 0;
    Player *highestBidder = nullptr;
    std::cout << "Начинается аукцион за " << property->getName() << " с начальной ценой " << property->getPrice() << "\n";

    bool auctionActive = true;
    while (auctionActive)
    {
        auctionActive = false;

        for (Player *player : players)
        {
            if (player != this)
            {
                std::cout << player->getName() << ", ваш текущий баланс: " << player->getBalance() << ".\n";
                int bid = makeBid(highestBid, player);

                if (bid > highestBid && player->canAfford(bid) == CAN_AFFORD)
                {
                    highestBid = bid;
                    highestBidder = player;
                    auctionActive = true;
                }
            }
        }
    }
    if (highestBidder)
    {
        highestBidder->pay(highestBid);
        highestBidder->addProperty(property);
        std::cout << highestBidder->getName() << " выигрывает аукцион и покупает " << property->getName() << " за " << highestBid << "\n";
    }
    else
    {
        std::cout << "Никто не сделал ставку. Аукцион завершен без победителя.\n";
    }
}

void Player::buy(Property *property)
{
    pay(property->getPrice());

    addProperty(property);
}

void Player::mortgageProperty(Property *property)
{
    property->mortgage();
    std::cout << "Игрок " << name << " заложил имущество \"" << property->getName()
              << "\" за " << property->calculateMortgage() << " монет.\n";
    totalPriceOfProperty -= property->calculateMortgage();
}

void Player::unmortgagedProperty(Property *property)
{
    int unMortgageCost = property->calculateUnMortgage();

    property->unMortgage(this);
    std::cout << "Игрок " << name << " выкупил имущество \"" << property->getName()
              << "\" за " << unMortgageCost << " монет.\n";
    totalPriceOfProperty += property->calculateMortgage();
}
