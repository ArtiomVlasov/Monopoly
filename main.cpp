#include <iostream>
#include "./src/game.hpp"
#include "./src/propertySubClasses.hpp"
#include "./src/player.hpp"
#include "time.h"
#define NUMSCELLS 40
int main()
{
    srand(time(NULL));
    int a;
    std::cout << "сколько будет игроков" << std::endl;
    std::cin >> a;
    if (a > 1 && a < 5)
    {
        Game *game = new Game(a, NUMSCELLS);
        game->start();
    }
    return 0;
}