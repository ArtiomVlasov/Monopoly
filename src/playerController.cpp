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

Player::AffordStatus playerController::playerCanAfford(int amount, Player* player)
{
    if (amount <= player->getBalance())
    {
        return Player::CAN_AFFORD;
    }
    if (amount >  player->getBalance() + 0)  //add from prop controller function
    {
        return Player::CANNOT_AFFORD;
    }
    return Player::NEED_TO_SELL_PROPERTY;
}

void playerController::playerDeclareBankruptcy(Player *creditor)
{
    Game::addBankruptPlayers(creditor);

    renderPlayerDeclareBankruptcy(creditor);
    if (creditor)
    {
        renderPlayerDeclareBankruptcyIfCreditor(creditor);
        for (Property *property : creditor->getListOfProperty())
        {
            playerAddProperty(property, creditor);
            renderPlayerDeclareBankruptcyIfCreditorGetPos(creditor, property);
        }
        playerReceive(creditor->getBalance(), creditor);
    }
    else
    {
        for (Property *property : creditor->getListOfProperty())
        {
            property->markAsAvailable();
        }
        propertyToBank();
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
        playerPay(street->getBuildingCost(), player);
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

int playerMakeBid(int currentHighestBid, Player *player)
{
    int bid = 0;
    renderPlayerMakeBid(currentHighestBid, player, 0, bid);
    std::cin >> bid; // не знаю наверно верно
    if (bid < 0)
    {
        renderPlayerMakeBid(currentHighestBid, player, 1, bid);
        return -1;
    }

    if (bid > currentHighestBid && playerController::playerCanAfford(bid, player) == Player::AffordStatus::CAN_AFFORD)
    {
        renderPlayerMakeBid(currentHighestBid, player, 2, bid);
        return bid;
    }
    else if (bid > currentHighestBid && playerController::playerCanAfford(bid, player) == Player::AffordStatus::CANNOT_AFFORD)
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


int playerController::playerMakeDicision(Player* player) {
    int decision;
    renderPlayerMakeDicision(player);
    std::cin >> decision;

    while (decision < 0 || decision > 2)
    {
        renderPlayerErrirMakeDicision();
        std::cin >> decision;
    }

    return decision;
}

void playerController::playerStartAuction(Property *property, const std::vector<Player *> &players, Player* player)
{
    int highestBid = 0;
    Player *highestBidder = nullptr;
    rednerPlayerStartAuction(0, player, property, highestBid);

    bool auctionActive = true;
    while (auctionActive)
    {
        auctionActive = false;

        for (Player *pl : players)
        {
            if (pl != player)
            {
                rednerPlayerStartAuction(1, player, property, highestBid);

                int bid = playerMakeBid(highestBid, pl);

                if (bid > highestBid && playerCanAfford(bid, pl) == Player::AffordStatus::CAN_AFFORD)
                {
                    highestBid = bid;
                    highestBidder = pl;
                    auctionActive = true;
                }
            }
        }
    }
    if (highestBidder) 
    {
        playerPay(highestBid, highestBidder);
        playerAddProperty(property, highestBidder);
        rednerPlayerStartAuction(2, player, property, highestBid);

    }
    else
    {
        rednerPlayerStartAuction(3, player, property, highestBid);
    }
}

void playerController::playerMortgageProperty(Property *property, Player* player)
{
    property->mortgage();
    renderpPlayerMortgageProperty(property, player);
    player->setBalance(-property->calculateMortgage());

}

void playerController::playerUnmortgagedProperty(Property* property,  Player* player) {
    property->unMortgage(player);
    renderpPlayerUnmortgageProperty(property, player);
    player->setBalance(property->calculateMortgage());
}

void playerController::playerMoveToNearestStation(Game *game, int posIndex, Player* player)
{
    int nearestStationPosition = -1;
    int minDistance = game->getBoardSize();

    for (const auto &cell : game->getBoard().getAllCells())
    {
        if (cell->getType() == CellType::PropRailway)
        {
            int distance = std::abs(player->getPosition());
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestStationPosition = posIndex;
            }
        }
    }

    if (nearestStationPosition != -1)
    {
        player->setPosition(nearestStationPosition);
        rednerplayerMoveToNearestStation(0, player->getPosition());
    }
    else
    {
       rednerplayerMoveToNearestStation(1, 0);
    }
}

