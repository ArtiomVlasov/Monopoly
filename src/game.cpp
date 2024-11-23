#include "game.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.hpp"
#include "TaxPrisonChance.hpp"
#include "playerController.hpp"
#include "prisonController.hpp"
#include "propertySubClassesController.hpp"
#include <cstdlib> // для system()

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

bool Game::isGameOver() const
{ // опистаь
    return isAllPlayersIsBankrupt;
}

void Game::caseMapToAction(int a, Player *player, playerController *playercontooller, prisonController *prisoncontroller)
{
    switch(a)
    {
    case 1:
        printSellChoice();
        int index = 0;
        printPropertyList(player->getListOfProperty());
        std::cin >> index; 
        playerController::playerSellProperty(player, player->getListOfProperty()[index]);
        break;
    case 2:
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
        StreetController *streetcontroller = new StreetController(street);

       if (playercontooller->playerCanBuildOn(Board::getPropertyFromCell(player->getPosition()), streetcontroller))
        {
            printHousePurchaseSuccess();
            break;
        }
        printHousePurchaseFailure();
        break;

    case 3:
        playerController::playerDeclareBankruptcy(nullptr, player);
        break;

    default:
        printInvalidChoice();
        break;
    }
}

void Game::start()
{
    // for (size_t _p = 0; _p < players.size(); _p++) {
    //     playerController pController = new playerController(players[])
    // }
    WelcomeThePlayers(players);
    prisonController *prisContoller = new prisonController(new Prison());
    while (!isGameOver())
    {
        drawBoard();
        for (int i = 0; i < numPlayers; i++)
        {
            displayPlayerInfo(players[i]);
        }
        playerController *playercontroller = new playerController(players[playerTurn]);
        prisonController *prisoncontoller = new prisonController(new Prison());
        takeTurn(prisContoller, playercontroller, prisContoller);
        clearConsole();
    }
}

void Game::nextPlayer()
{
    playerTurn++;
    playerTurn %= numPlayers;
}

void Game::takeTurn(prisonController *pc, playerController *playercontroller, prisonController *prisoncontroller)
{
    rollDice();
    if (prisonController::isInJail(players[playerTurn]))
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
                pc->payToExit(players[playerTurn]);
            }
            return;
        }
    }
    playerController::playerMakeMove(firstValue + secondValue, players[playerTurn]); // зачем нам поле PLayer?????????
    Cell *cell = board->getCell(players[playerTurn]->getPosition()).get();
    cell->defaultAction(players[playerTurn], this);
    displayMenu();

    int a;
    std::cin >> a;
    caseMapToAction(a, players[playerTurn], playercontroller, prisoncontroller);
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
