#include "game.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.cpp"
#include "TaxPrisonChance.hpp"

Game::Game(int numPlayers, int numCells)
{
    Board *board = new Board(numCells);
    this->board = board;
    std::string name;
    this->numPlayers = numPlayers;
    for (int index = 0; index < numPlayers; index++)
    {
        std::cout << "Имя игрока " << index;
        scanf("%s", &name);
        players.push_back(new Player(name));
    }
}

int Game::rollDice()
{
    firstDiceValue = std::rand() % 7;
    secondDiceValue = std::rand() % 7;
    return firstDiceValue + secondDiceValue;
}


bool Game::isGameOver() const{ // опистаь
    return false;
}

void Game::start()
{
    WelcomeThePlayers(players);
    while (!isGameOver())
    {
        drawBoard();
        for (int i = 0; i < numPlayers; i++)
        {
            displayPlayerInfo(*players[i]);
        }
        takeTurn();
    }
} 

int Game::getRollDice(){
    return firstDiceValue+secondDiceValue;
}

void Game::nextPlayer()
{
    playerTurn++;
    playerTurn %= numPlayers;
}

void Game::takeTurn()
{
    rollDice();
    if (players[playerTurn]->isInJail())
    {
        if (firstDiceValue == secondDiceValue) {
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
    players[playerTurn]->makeMove(firstDiceValue + secondDiceValue); 
    Cell *cell = board->getCell(players[playerTurn]->getPosition()).get();
    cell->defaultAction(players[playerTurn], this);
    displayMenu();

    int a;
    scanf("%d", &a);
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
