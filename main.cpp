#include <iostream>
#include "./src/game.hpp"
#include "./src/propertySubClasses.hpp"
#include "./src/player.hpp"
#define NUMSCELLS 40
int main()
{

    int a;
    std::cout << "сколько будет игроко" << std::endl;
    std::cin >> a;
    if (a > 1 && a < 5)
    {
        Game *game = new Game(a, NUMSCELLS);
        game->start();
    }
    return 0;
}