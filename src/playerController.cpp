#include "playerController.hpp"
#include "propertyController.hpp"
#include "propertySubClassesController.hpp"

playerController::playerController(Player *player):player(player){}

void playerController::playerMakeMove(int steps, Player *player)
{
    player->setPosition((player->getPosition() + steps) % 40);
}

void playerController::playerPay(int amount, Player *Iplayer)
{
    renderPayPlayer(Iplayer, amount);
    Iplayer->setBalance(Iplayer->getBalance() - amount);
}

void playerController::playerReceive(int amount, Player* Iplayer)
{
    renderReceivePlayer(Iplayer, amount);
    Iplayer->setBalance(Iplayer->getBalance() -amount);
}

void playerController::playerAddProperty(Property *property, Player* Iplayer)
{
    property->setOwner(Iplayer);
    Iplayer->pushListOfProperty(property);
}

playerController::AffordStatus playerController::playerCanAfford(int amount, Player *Iplayer)
{
    if (amount <= Iplayer->getBalance())
    {
        return playerController::CAN_AFFORD;
    }
    if (amount >  Iplayer->getBalance() + PropertyController::getTotalPriceOfProperty(Iplayer))  
    {
        return playerController::CANNOT_AFFORD;
    }
    return playerController::NEED_TO_SELL_PROPERTY;
}

void playerController::playerDeclareBankruptcy(Player *creditor, Player *Iplayer)
{
    Game::addBankruptPlayers(Iplayer);

    renderPlayerDeclareBankruptcy(Iplayer);
    if (creditor)
    {
        renderPlayerDeclareBankruptcyIfCreditor(creditor);
        for (Property *property : Iplayer->getListOfProperty())
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
            PropertyController::markAsAvailable(property);
        }
        propertyToBank();
    }
    std::vector<Property *> A = creditor->getListOfProperty();
    A.clear();
    creditor->setPosition(0);
}

bool playerController::playerCanBuildOn(Property *property, StreetController *streetCntl) const
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
    if (!streetCntl->isFullListOfStreet(player, street->getColor())) // FIXME isFullListOfProperty переопределить в street
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

void playerController::playerBuildStructure(Street *street, StreetController *streetCntl)
{
    if (playerCanBuildOn(street, streetCntl) && player->getBalance() >= streetCntl->getBuildingCost())
    {
        playerPay(streetCntl->getBuildingCost(), player);
        streetCntl->buildNewHouse();
 
        renderPlayerBuildStructure(street, player);
    }
    else if (player->getBalance() < streetCntl->getBuildingCost())
    {
        renderPlayerNotBuildStructure(street);
    }
}

void playerController::playerDestroyStructure(Street *street, StreetController *streetCntl)
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
    streetCntl->demolishHouse();
    renderPlayerDestroyStructure(street, player, 2);
}

int playerController::playerMakeBid(int currentHighestBid, Player *Iplayer)
{
    int bid = 0;
    renderPlayerMakeBid(currentHighestBid, Iplayer, 0, bid);
    std::cin >> bid; // не знаю наверно верно
    if (bid < 0)
    {
        renderPlayerMakeBid(currentHighestBid, Iplayer, 1, bid);
        return -1;
    }

    if (bid > currentHighestBid && playerCanAfford(bid, Iplayer) == playerController::AffordStatus::CAN_AFFORD)
    {
        renderPlayerMakeBid(currentHighestBid, Iplayer, 2, bid);
        return bid;
    }
    else if (bid > currentHighestBid && playerCanAfford(bid, Iplayer) == playerController::AffordStatus::CANNOT_AFFORD)
    {
        if (Iplayer->getBalance() >= currentHighestBid + 10)
        {
            renderPlayerMakeBid(currentHighestBid, Iplayer, 3, bid);
            return playerMakeBid(currentHighestBid, Iplayer);
        }
        else
        {
            renderPlayerMakeBid(currentHighestBid, Iplayer, 4, bid);
            return -1;
        }
    }
    else
    {
        renderPlayerMakeBid(currentHighestBid, Iplayer, 5, bid);
        return playerMakeBid(currentHighestBid, Iplayer);
    }
}


int playerController::playerMakeDicision(Player *Iplayer) {
    int decision;
    renderPlayerMakeDicision(Iplayer);
    std::cin >> decision;

    while (decision < 0 || decision > 2)
    {
        renderPlayerErrirMakeDicision();
        std::cin >> decision;
    }

    return decision;
}

void playerController::playerStartAuction(Property *property, const std::vector<Player *> &players, Player *Iplayer)
{
    int highestBid = 0;
    Player *highestBidder = nullptr;
    rednerPlayerStartAuction(0, Iplayer, property, highestBid);

    bool auctionActive = true;
    while (auctionActive)
    {
        auctionActive = false;

        for (Player *pl : players)
        {
            if (pl != Iplayer)
            {
                rednerPlayerStartAuction(1, Iplayer, property, highestBid);

                int bid = playerMakeBid(highestBid, Iplayer);

                if (bid > highestBid && playerCanAfford(bid, Iplayer) == playerController::AffordStatus::CAN_AFFORD)
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
        playerPay(highestBid, Iplayer);
        playerAddProperty(property, highestBidder);
        rednerPlayerStartAuction(2, Iplayer, property, highestBid);

    }
    else
    {
        rednerPlayerStartAuction(3, Iplayer, property, highestBid);
    }
}

void playerController::playerMortgageProperty(Property *property, PropertyController *propCntl)
{
    propCntl->mortgageProperty(player);
    renderpPlayerMortgageProperty(property, player);
    player->setBalance(PropertyController::calculateMortgage(property));

}

void playerController::playerUnmortgagedProperty(Property* property, PropertyController *propCntl) {
    propCntl->unMortgageProperty(player);
    renderpPlayerUnmortgageProperty(property, player);
    player->setBalance(PropertyController::calculateMortgage(property));
}

void playerController::playerMoveToNearestStation(Game *game, int posIndex, Player* Iplayer)
{
    int nearestStationPosition = -1;
    int minDistance = game->getBoardSize();

    for (const auto &cell : game->getBoard().getAllCells())
    {
        if (cell->getType() == CellType::PropRailway)
        {
            int distance = std::abs(Iplayer->getPosition());
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestStationPosition = posIndex;
            }
        }
    }

    if (nearestStationPosition != -1)
    {
        Iplayer->setPosition(nearestStationPosition);
        rednerplayerMoveToNearestStation(0, Iplayer->getPosition());
    }
    else
    {
       rednerplayerMoveToNearestStation(1, 0);
    }
}

int playerController::getOwnedPropertyCount(CellType type, Player *player)
{
    int countQuantityProperty = 0;
    for (const Property *property : player->getListOfProperty())
    {
        if (property->getType() == type)
        {
            countQuantityProperty++;
        }
    }
    return countQuantityProperty;
}

 void playerController::playerBuy(Property *property, Player *Iplayer)
 {
     playerPay(property->getPrice(), Iplayer);
     playerAddProperty(property, Iplayer);
 }
