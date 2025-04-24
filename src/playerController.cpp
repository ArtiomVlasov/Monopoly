#include "playerController.hpp"
#include "propertyController.hpp"
#include "propertySubClassesController.hpp"
#include "render.hpp"



playerController::playerController(Player *player) : player(player) {}

/*void playerController::playerMakeMove(int steps, Player *player)
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
    Iplayer->setBalance(Iplayer->getBalance() + amount);
}

void playerController::playerAddProperty(Property *property, Player* Iplayer)
{
    property->setOwner(Iplayer);
    Iplayer->pushListOfProperty(property);
}
*/
playerController::AffordStatus playerController::playerCanAfford(int amount)
{
    if (amount <= player->getBalance())
    {
        return playerController::CAN_AFFORD;
    }
    if (amount > player->getBalance() + this->getTotalPriceOfProperty())
    {
        return playerController::CANNOT_AFFORD;
    }
    return playerController::NEED_TO_SELL_PROPERTY;
}

void playerController::playerDeclareBankruptcy(Player *creditor, Game *game)
{
    game->addBankruptPlayers(player);

    renderPlayerDeclareBankruptcy(player);
    if (creditor)
    {
        renderPlayerDeclareBankruptcyIfCreditor(creditor);
        for (Property *property : player->getListOfProperty())
        {
            creditor->addProperty(property);
            renderPlayerDeclareBankruptcyIfCreditorGetPos(creditor, property);
        }
        creditor->setBalance(creditor->getBalance() + player->getBalance());
    }
    else
    {
        for (Property *property : player->getListOfProperty())
        {
            PropertyController *propCntl;
            if (property->getType() == CellType::Street)
            {
                Street *street = dynamic_cast<Street *>(property);
                propCntl = new StreetController(street);
            }
            else if (property->getType() == CellType::PropRailway)
            {
                Railway *railway = dynamic_cast<Railway *>(property);
                propCntl = new RailwayController(railway);
            }
            else if (property->getType() == CellType::PropUtilities)
            {
                Utilities *utilities = dynamic_cast<Utilities *>(property);
                propCntl = new UtilitiesController(utilities);
            }
            propCntl->markAsAvailable(property);
        }
        propertyToBank();
    }
    std::vector<Property *> A = player->getListOfProperty();
    A.clear();
    player->setPosition(0);
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
        renderPayPlayer(player, streetCntl->getBuildingCost());
        player->setBalance(player->getBalance() - streetCntl->getBuildingCost());
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

int playerController::playerMakeBid(int currentHighestBid, PropertyController *propCntl)
{
    int bid = 0;
    renderPlayerMakeBid(currentHighestBid, player, 0, bid);
    std::cin >> bid; // не знаю наверно верно
    if (bid < 0)
    {
        renderPlayerMakeBid(currentHighestBid, player, 1, bid);
        return -1;
    }

    if (bid > currentHighestBid && bid - currentHighestBid >= 10 && playerCanAfford(bid) == playerController::AffordStatus::CAN_AFFORD)
    {
        renderPlayerMakeBid(currentHighestBid, player, 2, bid);
        return bid;
    }
    else if (bid > currentHighestBid && playerCanAfford(bid) == playerController::AffordStatus::CANNOT_AFFORD)
    {
        if (player->getBalance() >= currentHighestBid + 10)
        {
            renderPlayerMakeBid(currentHighestBid, player, 3, bid);
            return playerMakeBid(currentHighestBid, propCntl);
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
        return playerMakeBid(currentHighestBid, propCntl);
    }
}

int playerController::playerMakeDicision()
{
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

void playerController::playerStartAuction(Property *property, const std::vector<Player *> &players, PropertyController *propCntl)
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
                rednerPlayerStartAuction(1, pl, property, highestBid);
                playerController *plCntl = new playerController(pl);
                int bid = plCntl->playerMakeBid(highestBid, propCntl);

                if (bid > highestBid)
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
        renderPayPlayer(highestBidder, highestBid);
        highestBidder->setBalance(highestBidder->getBalance() - highestBid);
        highestBidder->addProperty(property);
        rednerPlayerStartAuction(2, highestBidder, property, highestBid);
    }
    else
    {
        rednerPlayerStartAuction(3, player, property, highestBid);
    }
}

void playerController::playerMortgageProperty(Property *property)
{
    PropertyController *propCntl;
    if (property->getType() == CellType::Street)
    {
        Street *street = dynamic_cast<Street *>(property);
        propCntl = new StreetController(street);
    }
    else if (property->getType() == CellType::PropRailway)
    {
        Railway *railway = dynamic_cast<Railway *>(property);
        propCntl = new RailwayController(railway);
    }
    else if (property->getType() == CellType::PropUtilities)
    {
        Utilities *utilities = dynamic_cast<Utilities *>(property);
        propCntl = new UtilitiesController(utilities);
    }
    propCntl->mortgageProperty(player);
    renderpPlayerMortgageProperty(property, player, propCntl);
}

void playerController::playerUnmortgagedProperty(Property *property, PropertyController *propCntl)
{
    propCntl->unMortgageProperty(player);
    renderpPlayerUnmortgageProperty(property, player, propCntl);
    player->setBalance(propCntl->calculateMortgage());
}

void playerController::playerMoveToNearestStation(Player *Iplayer)
{
    const int stationPositions[] = {5, 15, 25, 35};
    const int totalStations = 4;
    int currentPosition = Iplayer->getPosition();

    int nearestStationPosition = -1;
    int minDistance = 39;

    for (int i = 0; i < totalStations; i++)
    {
        int stationPosition = stationPositions[i];
        int distance = (stationPosition - currentPosition + 39) % 40; // Расстояние по кругу

        if (distance < minDistance)
        {
            minDistance = distance;
            nearestStationPosition = stationPosition;
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

int playerController::getOwnedPropertyCount(CellType type)
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

void playerController::playerBuy(Property *property)
{
    renderPayPlayer(player, property->getPrice());
    player->setBalance(player->getBalance() - property->getPrice());
    player->addProperty(property);
}

int playerController::getTotalPriceOfProperty()
{
    int totalPrice = 0;
    for (Property *property : player->getListOfProperty())
    {
        if (property->getType() == CellType::Street)
        {
            Street *street = dynamic_cast<Street *>(property);
            StreetController *strCntl = new StreetController(street);
            totalPrice += strCntl->calculateMortgage();
        }
        else if (property->getType() == CellType::PropRailway)
        {
            Railway *railway = dynamic_cast<Railway *>(property);
            RailwayController *rlwCntl = new RailwayController(railway);
            totalPrice += rlwCntl->calculateMortgage();
        }
        else if (property->getType() == CellType::PropUtilities)
        {
            Utilities *utilities = dynamic_cast<Utilities *>(property);
            UtilitiesController *utlCntl = new UtilitiesController(utilities);
            totalPrice += utlCntl->calculateMortgage();
        }
    }
    return totalPrice;
}