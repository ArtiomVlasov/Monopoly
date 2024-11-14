#include <iostream>
#include <vector>
#include <render.hpp>
class Street;
class Property;

void Render::drawBoard()
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
                std::cout << "  " << properties[index] << "   |";
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
                std::cout << " " << properties[index] << "   |";
                printf("\t\t\t\t\t\t\t\t\t  ");
                std::cout << " " << properties[index + 1] << "   |" << std::endl;
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
                std::cout << "  " << properties[index] << "   |";
                index++;
            }
        }
        printf("\n");
    }
}

void Render::displayPlayerInfo(const Player &player) const
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

void Render::RenderCreateCell(std::string s, int flag)
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
