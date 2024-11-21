#include "playerController.hpp"

void playerController::playerMakeMove(int steps, Player *player)
{
    player->setPosition((player->getPosition() + steps) % 40);
}

void playerController::playerPay(int amount, Player *player)
{
    renderPayPlayer(player, amount);
    player->setBalance(-amount);
}

void playerController::playerReceive(int amount, Player *player)
{
    renderReceivePlayer(player, amount);
    player->setBalance(amount);
}

void playerController::playerAddProperty(Property *property, Player *player)
{
    player->setTotalPriceOfProperty(property->calculateMortgage());
    property->setOwner(player);
    player->pushListOfProperty(property);
}

// void playerController::playerCanAfford(int amount, Player* player) {

// }

void playerController::playerDeclareBankruptcy(Player *creditor)
{
    creditor->setBankrupt();

    renderPlayerDeclareBankruptcy(creditor);
    if (creditor)
    {
        std::cout << "Его имущество переходит к " << creditor->getName() << ".\n";
        for (Property *property : creditor->getListOfProperty())
        {
            creditor->addProperty(property);
            renderPlayerDeclareBankruptcyIfCreditorGetPos(creditor, property);
        }
        creditor->receive(creditor->getBalance());
    }
    else
    {
        for (Property *property : creditor->getListOfProperty())
        {
            property->markAsAvailable();
        }
        std::cout << "Его имущество возвращается банку и снова доступно для покупки.\n";
    }
    std::vector<Property *> A = creditor->getListOfProperty();
    A.clear();
    creditor->setPosition(0);
}

bool playerController::playerCanBuildOn(Property *property, Player *player) const
{
    Street *street = dynamic_cast<Street *>(property);
    if (!street)
    {
        renderPlayerCanBuildOn(player, 0);
        return false;
    }

    if (street->getOwner() != player)
    {
        renderPlayerCanBuildOn(player, 1);
        return false;
    }
    if (!street->isFullListOfStreet(player, street->getColor())) // FIXME isFullListOfProperty переопределить в street
    {
        renderPlayerCanBuildOn(player, 2);
        return false;
    }

    if (street->isMortgaged())
    {
        renderPlayerCanBuildOn(player, 3);
        return false;
    }

    if (street->getLevelOfStreet() == 5)
    {
        return false;
    }

    return true;
}

void playerController::playerBuildStructure(Street *street, Player *player)
{
    if (playerCanBuildOn(street, player) && player->getBalance() >= street->getBuildingCost())
    {
        player->pay(street->getBuildingCost());
        street->buildNewHouse();

        renderPlayerBuildStructure(street, player);
    }
    else if (player->getBalance() < street->getBuildingCost())
    {
        renderPlayerNotBuildStructure(street);
    }
}

void playerController::playerDestroyStructure(Street *street, Player *player)
{
    if (street->getOwner() != player)
    { // хз надо здесь проверять это
        renderPlayerDestroyStructure(street, player, 0);
        return;
    }

    if (street->getLevelOfStreet() == 1)
    {
        renderPlayerDestroyStructure(street, player, 1);
        return;
    }

    // Снос здания
    street->demolishHouse();
    renderPlayerDestroyStructure(street, player, 2);
}

int playerController::playerMakeBid(int currentHighestBid, Player *player)
{
    int bid = 0;
    renderPlayerMakeBid(currentHighestBid, player, 0, bid);
    std::cin >> bid; // не знаю наверно верно
    if (bid < 0)
    {
        renderPlayerMakeBid(currentHighestBid, player, 1, bid);
        return -1;
    }

    if (bid > currentHighestBid && player->canAfford(bid) == Player::AffordStatus::CAN_AFFORD)
    {
        renderPlayerMakeBid(currentHighestBid, player, 2, bid);
        return bid;
    }
    else if (bid > currentHighestBid && player->canAfford(bid) == Player::AffordStatus::CANNOT_AFFORD)
    {
        if (player->getBalance() >= currentHighestBid + 10)
        {
            renderPlayerMakeBid(currentHighestBid, player, 3, bid);
            return playerMakeBid(currentHighestBid, player);
        }
        else
        {
            renderPlayerMakeBid(currentHighestBid, player, 4, bid);
            return -1;
        }
    }
    else
    {
        renderPlayerMakeBid(currentHighestBid, player, 5, bid);
        return playerMakeBid(currentHighestBid, player);
    }
}
