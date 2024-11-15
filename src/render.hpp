#include <iostream>
#include <vector>
#include "player.hpp"
#include "property.hpp"


std::vector<std::string> listOFstreets = {
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

void drawBoard()
{
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 || i == 2)
            {
                printf("_______ ");
                continue;
            }
            else
            {
                std::cout << "  " << listOFstreets[index] << "   |";
                index++;
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0 || j == 2)
            {
                printf("______");
                printf("\t\t\t\t\t\t\t\t\t  ");
                printf("_______\n");
                continue;
            }
            else
            {
                std::cout << " " << listOFstreets[index] << "   |";
                printf("\t\t\t\t\t\t\t\t\t  ");
                std::cout << " " << listOFstreets[index + 1] << "   |" << std::endl;
                index++;
                index++;
                continue;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 || i == 2)
            {
                printf("_______ ");
                continue;
            }
            else
            {
                std::cout << "  " << listOFstreets[index] << "   |";
                index++;
            }
        }
        printf("\n");
    }
}

void displayPlayerInfo(const Player &player)
{
    std::cout << "Игрок: " << player.getName() << "\n";
    std::cout << "Баланс: " << player.getBalance() << "\n";
    std::cout << "Позиция на поле: " << player.getPosition() << "\n";
    std::cout << "В тюрьме: " << (player.isInJail() ? "Да" : "Нет") << "\n";
    std::cout << "Банкрот: " << (player.isBankrupt() ? "Да" : "Нет") << "\n";
    std::cout << "Недвижимость:\n";
    for (const Property *property : player.getProperties())
    {
        std::cout << " - " << property->getName() << "\n";
    }
    std::cout << "-------------------------------------\n";
}

void RenderCreateCell(std::string s, int flag)
{

    for (int index = 0; index < 10; index++)
    {
        if (flag == 1)
        {
            printf("                                             \n");
        }
        if (flag == 2)
        {
            printf("\n");
        }
        if (index == 0 || index == 9)
        {
            printf("____");
        }
        else if (index == 5)
        {
            printf("| %s |", s);
        }
        else
        {
            printf("          ");
        }
    }
}

void displayMenu()
{   
    std::cout << "Возможные действия в игре 'Монополия':n";
    std::cout << "1. Продать собственность";
    std::cout << "2. Построить дом/отель";
    std::cout << "3. Выйти из тюрьмы";
    std::cout << "4. Остаться в тюрьме";
    std::cout << "10. Объявить банкротствоn";
    std::cout << "11. Сделать предложение другим игрокамn";
    std::cout << "12. Применить карточку 'Выход из тюрьмы бесплатно'n";
    std::cout << "13. Сделать ход назад (если предусмотрено правилами)n";
    std::cout << "14. Завершить ходn";
}

void WelcomeThePlayers(std::vector<Player *> players)
{
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "Welcome To Monopoly!!!!!" << std::endl;
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "WARNING!!!!Before we start,please make the console window bigger in order to see the whole stuff...Width:140 and Height:60 should be OK!" << std::endl;
    std::cout << "If you have done the previous step,we are about to start" << std::endl;
    std::cout << "____________________________________________________________________________________________________________________" << std::endl;
    
}
