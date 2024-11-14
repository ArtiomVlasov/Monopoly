#include <iostream>
#include <vector>
#include <string>
#include "cell.hpp"
#include "player.hpp"
#include "property.hpp"
#include <vector>
#include <string>

void WelcomeThePlayers(std::vector<Player *> players)
{
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "Welcome To Monopoly!!!!!" << std::endl;
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "WARNING!!!!Before we start,please make the console window bigger in order to see the whole stuff...Width:140 and Height:60 should be OK!" << std::endl;
    std::cout << "If you have done the previous step,we are about to start" << std::endl;
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    goto loop1;
loop1:
    int index = 0;
    std::string name = "";
    for (Player *player : players)
    {
        std::cout << "Please enter the name of the " << index + 1 << " player:";
        scanf("%s", &name);
        if (name == "")
        {
            std::cout << "You didn't enter the name...Try again!" << std::endl;
            goto loop1;
        }
        players[index] = &Player(name);
    }
    std::cout << "Let's see who will start the game first" << std::endl;
}
class Render
{
    public:
        Render::Render();
        void RenderCreateCell(std::string s, int flag);
        std::vector<std::string> properties = {
            "FP", // Free Parking
            "KA", // Kentucky Avenue
            "CH", // Chance
            "IA", // Indiana Avenue
            "IL", // Illinois Avenue
            "BR", // B&O Railroad
            "AA", // Atlantic Avenue
            "VA", // Ventnor Avenue
            "WW", // Water Works
            "MG", // Marvin Gardens
            "GJ", // Go to Jail
            "NY", // New York Avenue
            "PA", // Pacific Avenue
            "TA", // Tennessee Avenue
            "NC", // North Carolina Avenue
            "CC", // Community Chest
            "SJ", // St. James Place
            "PA", // Pennsylvania Avenue
            "PR", // Pennsylvania Railroad
            "SL", // Short Line
            "VA", // Virginia Avenue
            "SA", // States Avenue
            "PP", // Park Place
            "EC", // Electric Company
            "LT", // LUXURY TAX
            "SC", // St. Charles Place
            "J",  // Jail
            "BW", // Boardwalk
            "JV", // Just Visiting
            "CA", // Connecticut Avenue
            "VA", // Vermont Avenue
            "OA", // Oriental Avenue
            "RR", // Reading Railroad
            "CT", // City Tax
            "BA", // Baltic Avenue
            "MA"  // Mediterranean Avenue
        };

        void drawBoard();

        void Render::displayPlayerInfo(const Player &player) const;
};
