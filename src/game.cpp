#include "game.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.hpp"
#include "TaxPrisonChance.hpp"
#include "playerController.hpp"
#include "TaxPrisonChanceCntl.hpp"
#include "propertySubClassesController.hpp"
#include <cstdlib> // для system()
#include <algorithm>

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
    firstValue = std::rand() % 7;
    secondValue = std::rand() % 7;
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
}

bool Game::isGameOver() const
{ // опистаь
    return isAllPlayersIsBankrupt;
}

void Game::sellProperty(Player *player, playerController *plrCntl)
{
    printSellChoice();
    int index = 1;
    while (index != 0)
    {
        printPropertyList(player->getListOfProperty());
        std::cin >> index;
        Property *property = player->getListOfProperty()[index];
        plrCntl->playerMortgageProperty(property);
    }
}

void Game::caseMapToAction(int a, Player *player, playerController *plrCntl, prisonController *prisonCntl)
{
    switch (a)
    {
    case 1:
    {
        sellProperty(player, plrCntl);
        break;
    }
    case 2:
    {
        printBuildHouseChoice();
        bool status = true;
        Street *street = nullptr;
        while (status)
        {
            std::string nameOFStreet;
            std::cin >> nameOFStreet;
            street = board->getStreetByName(nameOFStreet);
            if (street == nullptr)
            {
                printStreetNotFound();
                continue;
            }
            else
            {
                status = false;
            }
        }
        StreetController *strCntl = new StreetController(street);
        plrCntl->playerBuildStructure(street, strCntl);
        break;
    }
    case 3:
    {
        plrCntl->playerDeclareBankruptcy(nullptr, this);
        break;
    }
    case 4:
    {
        renderEndTurn(player);
        nextPlayer();
        break;
    default:
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
    prisonController *prisController = new prisonController(new Prison());
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
    /*if (pc->isInJail(players[playerTurn]))
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
    }*/

    players[playerTurn]->setPosition(players[playerTurn]->getPosition() + firstValue + secondValue);

    // plrCntl->playerMakeMove(firstValue + secondValue, players[playerTurn]); // зачем нам поле PLayer?????????
    CellContent *cell = board->getCell(players[playerTurn]->getPosition()).get();
    CellController *cellController;
    std::cout<<"___====_____________+++++\n";
    switch (cell->getType())
    {
    case CellType::Street:
    {
        StreetController *street = new StreetController(dynamic_cast<Street *>(cell));
        cellController = street;
    }
    case CellType::EmptyCell:
    {
        EmptyCellController *empty = new EmptyCellController();
        cellController = empty;
    }
    case CellType::Chance:
    {
        ChanceController *chance = new ChanceController(dynamic_cast<Chance *>(cell));
        cellController = chance;
    }
    case CellType::Prison:
    {
        prisonController *prison = new prisonController(dynamic_cast<Prison *>(cell));
        cellController = prison;
    }
    case CellType::PropRailway:
    {
        RailwayController *prop = new RailwayController(dynamic_cast<Railway *>(cell));
        cellController = prop;
    }
    case CellType::PropUtilities:
    {
        UtilitiesController *util = new UtilitiesController(dynamic_cast<Utilities *>(cell));
        cellController = util;
    }
    case CellType::publicTreasury:
    {
        PublicTreasuryController *tres = new PublicTreasuryController(dynamic_cast<PublicTreasury *>(cell));
        cellController = tres;
    }
    case CellType::Tax:
    {
        TaxController *tax = new TaxController(dynamic_cast<Tax *>(cell));
        cellController = tax;
    }
    }
    ArgsForDefAct *args = cellController->getArgs(players[playerTurn], this, plrCntl);
    std::cout<<"cweweco8899999999999999999\n";
    cellController->defaultAction(args);
    std::cout<<"";
    displayMenu();

    int decision;
    std::cin >> decision;
    caseMapToAction(decision, players[playerTurn], plrCntl, pc);
    // nextPlayer();
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