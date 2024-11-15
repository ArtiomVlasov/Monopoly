#include <game.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.hpp"

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

int Game::rollDice() const
{
    return std::rand() % 7;
}

void Game::start()
{
    WelcomeThePlayers(players);
    while (!isGameOver())
    {
        Render::drawBoard();
        for (int i = 0; i < numPlayers; i++) {
            Render::displayPlayerInfo(*players[i]);
        }
        takeTurn();
    }
}

void Game::nextPlayer() {
    playerTurn++;
    playerTurn %= numPlayers;
}

void Game::takeTurn()
{
    players[playerTurn]->setPosition(players[playerTurn]->getPosition() + rollDice());
    Cell *cell = board.getCell(players[playerTurn]->getPosition()).get();
    // добавить defualtACton !!
    Render::displayMenu();

    int a;
    std::cin >> "ВВОД какое действие хотите соверить : ">> a;
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
