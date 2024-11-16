#include "game.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.hpp" // без него ругается
#include "render.hpp"
#include "TaxPrisonChance.hpp"

Game::Game(int numPlayers, int numCells)
{
    Board *board = new Board(numCells);
    this->board = board;
    std::string name;
    this->numPlayers = numPlayers;
    for (int index = 0; index < numPlayers; index++)
    {
        std::cout << "Имя игрока " << index+1 << ": ";
        std::cin>>name;
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


bool Game::isGameOver() const{ // опистаь
    return false;
}   

void Game::caseMapToAction(int a) {
     switch (a)
    {
    case 1:
        std::cout << "Вы выбрали: Купить\n";
        // players[playerTurn]->buy(); как передать prop?
        break;
    case 2:
        std::cout << "Вы выбрали: Продать\n";
        // Логика продажи
        break;
    case 3:
        std::cout << "Вы выбрали: Построить дом\n";
        // Логика постройки дома
        break;
    case 4:
        std::cout << "Вы выбрали: Собрать аренду\n";
        // Логика сбора аренды
        break;
    case 5:
        std::cout << "Вы выбрали: Пас\n";
        // Логика пропуска хода
        break;
    case 0:
        std::cout << "Выход из игры\n";
        break;
    default:
        std::cout << "Неверный выбор, попробуйте снова\n";
        break;
    }
}

void Game::start()
{
    WelcomeThePlayers(players);
    while (!isGameOver())
    {
        drawBoard();
        for (int i = 0; i < numPlayers; i++)
        {
            displayPlayerInfo(players[i]);
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
  
    rollDice();
    if (players[playerTurn]->isInJail())
    {
        if (firstValue == secondValue) {
            players[playerTurn]->releaseFromJail();
        }
        else {
            std::cout << "Вы можете заплатить " << Prison::getJailFee() << "нажмите 1 если хотите 0 если нет\n";
            int answer;
            std::cin >> answer;
            if (answer == 1)
            {
                // players[playerTurn]->pay(Prison::getJailFee());
                players[playerTurn]->payToExit(Prison::getJailFee());
            }
            return;
        }    
    }
    players[playerTurn]->makeMove(firstValue + secondValue); 
    printf("%d %d\n",firstValue, secondValue );
    Cell *cell = board->getCell(0).get();
    //printf("_________________________- %d\n", players[playerTurn]->getPosition());
    cell->defaultAction(players[playerTurn], this);
    displayMenu();

    int a;
    std::cin>>a;
    caseMapToAction(a);
    nextPlayer();
}

int Game::getBoardSize() {
    return players.size();
}

Board Game::getBoard() {
    return *board;
}

std::vector<Player *>Game:: getListOfPlayers() {
    return players;
}

int Game::getRollDice(){
    return firstValue+secondValue;
}

void Game::sellProperty(Player* player) {
    int a;
    std::cin >> a;
    caseMapToAction(a);
    // if (player->getBalance() < MuchIt) {
    //     while(player->getBalance() < MuchIt) {
    //         int a;
    //         std::cin("%d", &a);
    //         caseMapToAction(a);
    //     }    
    // }
}