#include <game.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.hpp"
#include "TaxPrisonChance.hpp"

Game::Game(int numPlayers, int numCells)
{
    Board *board = new Board(numCells);
    // this->board = board; add
    std::string name;
    this->numPlayers = numPlayers;
    for (int index = 0; index < numPlayers; index++)
    {
        std::cout << "Имя игрока " << index;
        scanf("%s", &name);
        players.push_back(new Player(name));
    }
}

int Game::rollDice(gameRollValue gamerollvalue) const
{
    gamerollvalue.firstValue = std::rand() % 7;
    gamerollvalue.secondValue = std::rand() % 7;
    return gamerollvalue.firstValue + gamerollvalue.secondValue;
}

void Game::start()
{
    WelcomeThePlayers(players);
    while (!isGameOver())
    {
        Render::drawBoard();
        for (int i = 0; i < numPlayers; i++)
        {
            Render::displayPlayerInfo(*players[i]);
        }
        takeTurn();
    }
}

void Game::nextPlayer()
{
    playerTurn++;
    playerTurn %= numPlayers;
}

void Game::takeTurn()
{
    gameRollValue gamerollvalue;
    rollDice(gamerollvalue);
    if (players[playerTurn]->isInJail())
    {
        if (gamerollvalue.firstValue == gamerollvalue.secondValue) {
            players[playerTurn]->releaseFromJail();
        }
        else {
            std::cout << "Вы можете заплатить " << Prison::getJailFee() << "нажмите 1 если хотите 0 если нет";
            int answer;
            scanf("%d", &answer);
            if (answer == 1)
            {
                // players[playerTurn]->pay(Prison::getJailFee());
                players[playerTurn]->payToExit(Prison::getJailFee());
            }
            return;
        }    
    }
    players[playerTurn]->makeMove(gamerollvalue.firstValue + gamerollvalue.secondValue); 
    Cell *cell = board.getCell(players[playerTurn]->getPosition()).get();
    cell->defaultAction(players[playerTurn], this);
    Render::displayMenu();

    int a;
    std::cin >> "ВВОД какое действие хотите соверить : " >> a;
    switch (a)
    {
    case 1:
        std::cout << "Вы выбрали: Купить.n";
        // players[playerTurn]->buy(); как передать prop?
        break;
    case 2:
        std::cout << "Вы выбрали: Продать.n";
        // Логика продажи
        break;
    case 3:
        std::cout << "Вы выбрали: Построить дом.n";
        // Логика постройки дома
        break;
    case 4:
        std::cout << "Вы выбрали: Собрать аренду.n";
        // Логика сбора аренды
        break;
    case 5:
        std::cout << "Вы выбрали: Пас.n";
        // Логика пропуска хода
        break;
    case 0:
        std::cout << "Выход из игры.n";
        break;
    default:
        std::cout << "Неверный выбор, попробуйте снова.n";
        break;
    }
}
