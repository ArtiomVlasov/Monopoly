#include "game.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp"
#include "render.hpp"
#include "TaxPrisonChance.hpp"
#include "playerController.hpp"
#include "TaxPrisonChanceCntl.hpp"
#include "propertySubClassesController.hpp"
#include <cstdlib> // для system()
#include <algorithm>
#include "../json.hpp"

void clearConsole()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux / macOS
#endif
}

Game::Game(int numPlayers, int numCells)
{
    Board *board = new Board(numCells, this);

    this->board = board;
    std::string name;
    this->numPlayers = numPlayers;
    for (int index = 0; index < numPlayers; index++)
    {
        std::cout << "Имя игрока " << index + 1 << ": ";
        std::cin >> name;
        players.push_back(new Player(name));
    }
    playerTurn = 0;
}

int Game::rollDice()
{
    firstValue = std::rand() % 6 + 1;
    secondValue = std::rand() % 6 + 1;
    return firstValue + secondValue;
}

bool Game::isBankruptPlayer(Player *player)
{
    auto a = std::find(bankruptPlayers.begin(), bankruptPlayers.end(), player);
    return a != bankruptPlayers.end();
}

void Game::addBankruptPlayers(Player *player)
{
    bankruptPlayers.push_back(player);
    std::vector<Player *> pl = getBankruptPlayers();
    if (pl.size() == numPlayers){
        isAllPlayersIsBankrupt = true;
    }
}

bool Game::isGameOver() const
{ // опистаь
    return isAllPlayersIsBankrupt;
}

void Game::sellProperty(Player *player, playerController *plrCntl)
{
    printSellChoice();
    int index;
    printPropertyList(player->getListOfProperty());
    std::cin >> index;
    while (index != 0)
    {
        Property *property = player->getListOfProperty()[index - 1];
        if (!property->isMortgaged())
        {
            plrCntl->playerMortgageProperty(property);
        }
        else
        {
            printCantMortgage(property);
        }
        printPropertyList(player->getListOfProperty());
        std::cin >> index;
    }
}

void Game::caseMapToAction(int decision, Player *player, playerController *plrCntl, prisonController *prisonCntl)
{
    switch (decision)
    {
    case 1:
    {
        sellProperty(player, plrCntl);
        break;
    }
    case 2:
    {
        printBuildHouseChoice();
        if (plrCntl->getOwnedPropertyCount(CellType::Street) != 0)
        {

            printStreets(player->getListOfProperty());
            bool status = true;
            Street *street = nullptr;
            int decision;
            std::cin >> decision;
            while (decision != 0)
            {
                int counterOfStreet = 0;
                for (Property *property : player->getListOfProperty())
                {
                    if (property->getType() == CellType::Street)
                    {
                        counterOfStreet++;
                        if (counterOfStreet == decision)
                        {
                            street = dynamic_cast<Street *>(property);
                            decision = 0;
                            break;
                        }
                    }
                }
                if (street == nullptr)
                {
                    printStreetNotFound();
                    std::cin >> decision;
                    continue;
                }
            }
            if (street != nullptr)
            {
                StreetController *strCntl = new StreetController(street);
                plrCntl->playerBuildStructure(street, strCntl);
            }
        }
        else
        {
            printNoStreetsInChose(player);
        }
        break;
    }
    case 3:
    {
        plrCntl->playerDeclareBankruptcy(nullptr, this);
        break;
    }

    default:
    {
        printInvalidChoice();
        break;
    }
    }
}

void Game::start()
{
    // for (size_t _p = 0; _p < players.size(); _p++) {
    //     playerController pController = new playerController(players[])
    // }
    WelcomeThePlayers(players);
    Prison *prison = new Prison();
    prisonController *prisController = new prisonController(prison);
    while (!isGameOver())
    {
        drawBoard();
        for (int i = 0; i < numPlayers; i++)
        {
            displayPlayerInfo(players[i], this, prisController);
        }
        playerController *playercontroller = new playerController(players[playerTurn]);

        takeTurn(prisController, playercontroller);
        clearConsole();
    }
}

void Game::nextPlayer()
{
    playerTurn++;
    playerTurn %= numPlayers;
}

void Game::takeTurn(prisonController *pc, playerController *plrCntl)
{
    rollDice();
    std::cout << this->getRollDice() << "\n";
    if (pc->isInJail(players[playerTurn]))
    {
        if (firstValue == secondValue)
        {
            pc->playerReleaseFromJail(players[playerTurn]);
        }
        else
        {
            std::cout << "Вы можете заплатить " << pc->getPrison()->getJailFee() << "нажмите 1 если хотите 0 если нет\n";
            int answer;
            std::cin >> answer;
            if (answer == 1)
            {
                pc->payToExit(players[playerTurn], plrCntl);
            }
            return;
        }
    }

    players[playerTurn]->setPosition(players[playerTurn]->getPosition() + firstValue + secondValue);

    // plrCntl->playerMakeMove(firstValue + secondValue, players[playerTurn]); // зачем нам поле PLayer?????????
    CellContent *cell = board->getCell(players[playerTurn]->getPosition()).get();
    CellController *cellController;
    switch (cell->getType())
    {
    case CellType::Street:
    {
        Street *street = dynamic_cast<Street *>(cell);
        StreetController *streetcntl = new StreetController(street);
        cellController = streetcntl;
        break;
    }
    case CellType::EmptyCell:
    {
        EmptyCellController *empty = new EmptyCellController(dynamic_cast<EmptyCell *>(cell));
        cellController = empty;
        break;
    }
    case CellType::Chance:
    {
        ChanceController *chance = new ChanceController(dynamic_cast<Chance *>(cell));
        cellController = chance;
        break;
    }
    case CellType::Prison:
    {
        prisonController *prison = new prisonController(dynamic_cast<Prison *>(cell));
        cellController = prison;
        break;
    }
    case CellType::PropRailway:
    {
        RailwayController *prop = new RailwayController(dynamic_cast<Railway *>(cell));
        cellController = prop;
        break;
    }
    case CellType::PropUtilities:
    {
        UtilitiesController *util = new UtilitiesController(dynamic_cast<Utilities *>(cell));
        cellController = util;
        break;
    }
    case CellType::publicTreasury:
    {
        PublicTreasuryController *tres = new PublicTreasuryController(dynamic_cast<PublicTreasury *>(cell));
        cellController = tres;
        break;
    }
    case CellType::Tax:
    {
        TaxController *tax = new TaxController(dynamic_cast<Tax *>(cell));
        cellController = tax;
        break;
    }
    }
    ArgsForDefAct *args = cellController->getArgs(players[playerTurn], this, plrCntl);
    cellController->defaultAction(args);
    std::cout << "";
    int decision;
    displayMenu();
    std::cin >> decision;
    while (decision != 4)
    {
        caseMapToAction(decision, players[playerTurn], plrCntl, pc);
        if(decision == 3){
            break;
        }
        displayMenu();
        std::cin >> decision;
    }
    renderEndTurn(players[playerTurn]);
    nextPlayer();
}

int Game::getBoardSize()
{
    return players.size();
}

Board Game::getBoard()
{
    return *board;
}

std::vector<Player *> Game::getListOfPlayers()
{
    return players;
}

int Game::getRollDice()
{
    return firstValue + secondValue;
}

std::vector<Player *> Game::getBankruptPlayers()
{
    return bankruptPlayers;
}