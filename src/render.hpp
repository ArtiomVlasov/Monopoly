#include <iostream>
#include <vector>
#include "player.hpp"
#include "property.hpp"


std::vector<std::pair<std::string, std::string>> listOFstreets = {
    {"GO", "GO"},
    {"Mediterranean Avenue", "MA"},
    {"Community Chest", "CC"},
    {"Baltic Avenue", "BA"},
    {"Income Tax", "IT"},
    {"Reading Railroad", "RR"},
    {"Oriental Avenue", "OA"},
    {"Chance", "CH"},
    {"Vermont Avenue", "VA"},
    {"Connecticut Avenue", "CA"},
    {"Jail (Just Visiting)", "JV"},
    {"St. Charles Place", "SC"},
    {"Electric Company", "EC"},
    {"States Avenue", "SA"},
    {"Virginia Avenue", "VA"},
    {"Pennsylvania Railroad", "PR"},
    {"St. James Place", "SJ"},
    {"Community Chest", "CC"},
    {"Tennessee Avenue", "TA"},
    {"New York Avenue", "NY"},
    {"Jail (Just Visiting)", "JV"},
    {"Kentucky Avenue", "KA"},
    {"Chance", "CH"},
    {"Indiana Avenue", "IA"},
    {"Illinois Avenue", "IA"},
    {"B&O Railroad", "BR"},
    {"Atlantic Avenue", "AA"},
    {"Ventnor Avenue", "VA"},
    {"Water Works", "WW"},
    {"Marvin Gardens", "MG"},
    {"Pacific Avenue", "PA"},
    {"North Carolina Avenue", "NC"},
    {"Community Chest", "CC"},
    {"Pennsylvania Avenue", "PA"},
    {"Short Line Railroad", "SL"},
    {"Chance", "CH"},
    {"Park Place", "PP"},
    {"Luxury Tax", "LT"},
    {"Boardwalk", "BW"},
    {"Jail (Just Visiting)", "JV"}
};

// Удаляем дубликаты и сортируем по порядку, если необходимо.


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
                std::cout << "  " << listOFstreets[index].second << "   |";
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
                std::cout << " " << listOFstreets[index].second << "   |";
                printf("\t\t\t\t\t\t\t\t\t  ");
                std::cout << " " << listOFstreets[index].second << "   |" << std::endl;
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
                std::cout << "  " << listOFstreets[index].second << "   |";
                index++;
            }
        }
        printf("\n");
    }
}

void displayPlayerInfo(Player *player)
{
    std::cout << "Игрок: " << player->getName() << "\n";
    std::cout << "Баланс: " << player->getBalance() << "\n";
    std::cout << "Позиция на поле: " << player->getPosition() << "\n";
    std::cout << "В тюрьме: " << (player->isInJail() ? "Да" : "Нет") << "\n";
    std::cout << "Банкрот: " << (player->isBankrupt() ? "Да" : "Нет") << "\n";
    std::cout << "Недвижимость:\n";
    for (const Property *property : player->getProperties())
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
    std::cout << "Возможные действия в игре 'Монополия':\n";
    std::cout << "1. Продать собственность\n";
    std::cout << "2. Построить дом/отель\n";
    std::cout << "3. Выйти из тюрьмы\n";
    std::cout << "4. Остаться в тюрьме\n";
    std::cout << "5. Объявить банкротствоn\n";
    std::cout << "6. Сделать предложение другим игрокам\n";
    std::cout << "7. Применить карточку 'Выход из тюрьмы бесплатно'\n";
    std::cout << "8. Сделать ход назад (если предусмотрено правилами)\n";
    std::cout << "9. Завершить ход\n";
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
