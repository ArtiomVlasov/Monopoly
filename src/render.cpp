#include "render.hpp"
#include <iostream>
#include <vector>
#include "player.hpp"
#include "property.hpp"
#include "propertySubClasses.hpp"
#include "TaxPrisonChanceCntl.hpp"
#include "propertyController.hpp"

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
    {"Jail (Just Visiting)", "JV"}};

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

void displayPlayerInfo(Player *player, Game *game, prisonController *prisonCntl)
{
    std::cout << "Игрок: " << player->getName() << "\n";
    std::cout << "Баланс: " << player->getBalance() << "\n";
    std::cout << "Позиция на поле: " << player->getPosition() << "\n";
    std::cout << "В тюрьме: " << (prisonCntl->isInJail(player) ? "Да" : "Нет") << "\n";
    std::cout << "Банкрот: " << (game->isBankruptPlayer(player) ? "Да" : "Нет") << "\n";
    std::cout << "Недвижимость:\n";
    for (Property *property : player->getListOfProperty())
    {
        std::cout << " - " << property->getName();
        if (property->isMortgaged())
        {
            std::cout << " (Заложено)\n";
        }
        else
        {
            std::cout << " \n";
        }
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
    // std::cout << "3. Выйти из тюрьмы\n";
    // std::cout << "4. Остаться в тюрьме\n";
    std::cout << "3. Объявить банкротствоn\n";
    // std::cout << "4. Сделать предложение другим игрокам\n";
    // std::cout << "7. Применить карточку 'Выход из тюрьмы бесплатно'\n";
    // std::cout << "8. Сделать ход назад (если предусмотрено правилами)\n";
    std::cout << "4. Завершить ход\n";
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

void renderPayPlayer(Player *player, int amount)
{
    std::cout << "С баланса игрока " << player->getName() << " списано " << amount << " монет.\n";
}

void renderReceivePlayer(Player *player, int amount)
{
    std::cout << "Игрок " << player->getName() << " получает " << amount << " монет.\n";
}

void renderPlayerDeclareBankruptcy(Player *creditor)
{
    std::cout << "Игрок " << creditor->getName() << " не может оплатить ренту и объявляет банкротство.\n";
}

void renderPlayerDeclareBankruptcyIfCreditor(Player *creditor)
{
    std::cout << "Его имущество переходит к " << creditor->getName() << ".\n";
}

void renderPlayerDeclareBankruptcyIfCreditorGetPos(Player *creditor, Property *property)
{
    std::cout << property->getName() << " переходит к " << creditor->getName() << ".\n";
}

void propertyToBank()
{
    std::cout << "Его имущество возвращается банку и снова доступно для покупки.\n";
}

void renderPlayerCanBuildOn(Player *player, int flag)
{
    if (flag == 0)
    {
        std::cout << "Невозможно построить, так как это не улица.\n";
    }
    else if (flag == 1)
    {
        std::cout << "Улица не принадлежит игроку " << player->getName() << ".\n";
    }
    else if (flag == 2)
    {
        std::cout << "Игрок должен владеть всей цветовой группой, чтобы строить здесь.\n";
    }
    else if (flag == 3)
    {
        std::cout << "Невозможно построить, пока улица заложена.\n";
    }
}

void renderPlayerBuildStructure(Street *street, Player *player)
{
    std::cout << "Игрок " << player->getName() << " построил здание на \"" << street->getName()
              << "\". Уровень улицы теперь: " << street->getLevelOfStreet() << ".\n";
}

void renderPlayerNotBuildStructure(Street *street)
{
    std::cout << "Недостаточно средств для строительства на \"" << street->getName() << "\".\n";
}

void renderPlayerDestroyStructure(Street *street, Player *player, int status)
{
    if (status == 0)
    {
        std::cout << "Игрок " << player->getName() << " не владеет этой улицей.\n";
    }
    if (status == 1)
    {
        std::cout << "На улице " << street->getName() << " нет построек для сноса.\n";
    }
    if (status == 2)
    {
        std::cout << "Игрок " << player->getName() << " снес одну структуру на " << street->getName() << ".\n";
    }
}

void renderPlayerMakeBid(int currentHighestBid, Player *player, int status, int bid)
{
    switch (status)
    {
    case 0:
        std::cout << player->getName() << ", текущая наивысшая ставка: " << currentHighestBid << ". Введите вашу ставку или -1 для выхода: ";
        std::cout << "Наименьшая ставка 10М. \n";
        break;
    case 1:
        std::cout << player->getName() << " выходит из аукциона.\n";
        break;
    case 2:
        std::cout << player->getName() << " сделал ставку: " << bid << "\n";
        break;
    case 3:
        std::cout << player->getName() << ", Ваш баланс должен быть не меньше ставки, которую вы хотите сделать. Снизьте ставку.\n";
        break;
    case 4:
        std::cout << "У " << player->getName() << ", не хватает денег, он выходит из аукциона.\n";
        break;
    case 5:
        std::cout << player->getName() << ", Ставка должна быть выше текущей наивысшей ставки и минимум 10М.\n";
        break;
    default:
        std::cout << "Неизвестный статус.\n";
        break;
    }
}

void renderPlayerMakeDicision(Player *player)
{
    std::cout << "Игрок " << player->getName() << ", вы попали на недвижимость.\n";
    std::cout << "Выберите действие:\n";
    std::cout << "0 - Купить недвижимость\n";
    std::cout << "1 - Начать аукцион\n";
    std::cout << "Введите ваш выбор: ";
}

void renderPlayerErrirMakeDicision()
{
    std::cout << "Неверный выбор. Пожалуйста, введите 0, 1 или 2: ";
}

void rednerPlayerStartAuction(int status, Player *player, Property *property, int highestBid)
{
    switch (status)
    {
    case 0:
        std::cout << "Начинается аукцион за " << property->getName() << " с начальной ценой " << property->getPrice() << "\n";
        break;
    case 1:
        std::cout << player->getName() << ", ваш текущий баланс: " << player->getBalance() << ".\n";
        break;
    case 2:
        std::cout << player->getName() << " выигрывает аукцион и покупает " << property->getName() << " за " << highestBid << "\n";
        break;
    case 3:
        std::cout << "Никто не сделал ставку. Аукцион завершен без победителя.\n";
        break;
    default:
        std::cout << "Неизвестный статус.\n";
        break;
    }
}

void renderpPlayerMortgageProperty(Property *property, Player *player, PropertyController *propCntl)
{
    std::cout << "Игрок " << player->getName() << " заложил имущество \"" << property->getName()
              << "\" за " << propCntl->calculateMortgage() << " монет.\n";
}

void renderpPlayerUnmortgageProperty(Property *property, Player *player, PropertyController *propCntl)
{

    std::cout << "Игрок " << player->getName() << " выкупил имущество \"" << property->getName()
              << "\" за " << propCntl->calculateUnMortgage() << " монет.\n";
}

void rednerplayerMoveToNearestStation(int status, int position)
{
    if (status == 0)
    {
        std::cout << "Игрок перемещен на ближайшую станцию на позиции " << position << ".\n";
    }
    else
    {
        std::cout << "Станции не найдены на игровом поле.\n";
    }
}

void rednerPlayerAfterPRison(std::string name)
{
    std::cout << name << " заплатил и вышел из тюрьмы";
}
void rednerPlayerNoPRison(std::string name)
{
    std::cout << name << " не хватает денег";
}

void renderPayPlater(Player *player, int amount, Property *property)
{
    std::cout << "Игрок " << player->getName() << " платит ренту в размере " << amount << " монет игроку " << property->getOwner()->getName() << ".\n";
}

void printSellChoice()
{
    std::cout << "Вы выбрали: Продать. \n";
}

void printCantMortgage(Property *property)
{
    std::cout << "Вы не можете заложить это имущество, оно уже заложено! \n";
}

void printPropertyList(const std::vector<Property *> &properties)
{
    std::cout << "Выберете что хотите продать? Номер: ";
    for (int index = 0; index < properties.size(); index++)
    {
        std::cout << index + 1 << " " << properties[index]->getName();
        if (properties[index]->isMortgaged())
        {
            std::cout << "(Заложено) \n";
        }
        else
        {
            std::cout << "\n";
        }
    }
    std::cout << "Если не хотите ничего продавать, нажмите 0.\n";
}

void printStreets(const std::vector<Property *> &properties)
{
    std::cout << "Выберете на какой улице хотите построить дом? \nЕсли не хотите ничего строить, нажмите 0\n";
    for (int index = 0; index < properties.size(); index++)
    {
        if (properties[index]->getType() == CellType::Street)
        {
            std::cout << "Номер: " << index + 1 << " " << properties[index]->getName();
            if (properties[index]->isMortgaged())
            {
                std::cout << "(Заложено) \n";
            }
            else
            {
                std::cout << "\n";
            }
        }
    }
}

void printBuildHouseChoice()
{
    std::cout << "Вы выбрали: Построить дом\n";
}

void printNoStreetsInChose(Player *player)
{
    std::cout << "У вас нет улиц во владении!\n";
}

void printStreetNotFound()
{
    std::cout << "Нет такого имени\n";
}

void printHousePurchaseSuccess()
{
    std::cout << "Вы купили дом\n";
}

void printHousePurchaseFailure()
{
    std::cout << "Вы не можете купить дом\n";
}

void printInvalidChoice()
{
    std::cout << "Неверный выбор, попробуйте снова\n";
}

void renderEndTurn(Player *player)
{
    std::cout << "Игрок " << player->getName() << "завершил ход \n";
}