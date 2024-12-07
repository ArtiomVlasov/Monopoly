#include "player.hpp"
#include "property.hpp"
#include "deserializeJson.hpp"
#include "cellContent.hpp"
#include "propertySubClasses.hpp"
#include <iostream>
#include <fstream>
#include <vector>


CellType getTypeByNum(int num) 
{
    switch (num)
    {
    case 0:
        return CellType::Street;
    case 1:
        return CellType::PropRailway;
    case 2:
        return CellType::PropUtilities;
    case 3:
        return CellType::Chance;
     case 4:
        return CellType::Tax;
    case 5:
        return CellType::EmptyCell;
    case 6:
        return CellType::publicTreasury;
    case 7:
        return CellType::Prison;
    }
}

nlohmann::json toJson(Player *player)
{
    nlohmann::json j;
    if (player)
    {
        j["name"] = player->getName();
        j["balance"] = player->getBalance();
        j["position"] = player->getPosition();
        std::vector<Property *> list = player->getListOfProperty();
        for (Property *property : list)
        {
            nlohmann::json propJson;
            propJson["type"] = property->getType();
            propJson["name"] = property->getName();
            propJson["price"] = property->getPrice();
            propJson["rent"] = property->getRent();
            propJson["isMortgage"] = property->isMortgaged();
            if (property->getType() == CellType::Street)
            {
                Street *street = dynamic_cast<Street *>(property);
                propJson["color"] = street->getColor();
                propJson["level"] = street->getLevelOfStreet();
            }
            if (property->getOwner())
            {
                propJson["owner"] = property->getOwner()->getName();
            }
            else
            {
                propJson["owner"] = nullptr;
            }
            j["listOfProperty"].push_back(propJson);
        }
    }

    return j;
}

std::vector<Player *> fromJson(std::ifstream &inFile)
{
    std::vector<Player *> result;
    nlohmann::json j;
    if (!inFile.is_open())
    {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return std::vector<Player *>();
    }
    try
    {
        inFile >> j;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
        return std::vector<Player *>();
    }
    if (j.is_array())
    {
        for (const auto &item : j)
        {
            std::string name = item["name"];
            int balance = item["balance"];
            int position = item["position"];

            Player *player = new Player(name);
            player->setBalance(balance);
            player->setPosition(position);
            if (!item.contains("listOfProperty")) {
                result.push_back(player);
                break;
            }

            if (item.contains("listOfProperty"))
            {
                for (const auto &propJson : item["listOfProperty"])
                {
                    if (!propJson.is_object())
                    {
                        continue;
                    }
                    CellType type = getTypeByNum(propJson["type"]);
                    std::string propertyName = propJson["name"];
                    int price = propJson["price"];
                    int rent = propJson["rent"];
                    Street::Color colorName;
                    int level;
                    bool isMortage = propJson["isMortgage"];
                    if (type == CellType::Street)
                    {
                        colorName = propJson["color"];
                        level = propJson["level"];
                    }
                    Player *owner = nullptr;
                    Property *property;
                    switch (type)
                    {
                    case CellType::Street: // Street(std::string name, int price, int rent, Color color);
                    {
                        Street *street = new Street(propertyName, price, rent, player, isMortage, colorName, level);
                        property = street;
                        break;
                    }
                    case CellType::PropRailway:
                    {
                        Railway *prop = new Railway(propertyName, price, rent, isMortage, player);
                        property = prop;
                        break;
                    }
                    case CellType::PropUtilities:
                    {
                        Utilities *prop = new Utilities(propertyName, price, rent, isMortage, player);
                        property = prop;
                        break;
                    }
                    }
                    std::vector<Property *> A = player->getListOfProperty();
                    A.push_back(property);
                    result.push_back(player);
                }
            }
        }
    }
    return result;
}

nlohmann::json addPlayers(std::vector<Player *> players, std::ofstream &outFile)
{
    nlohmann::json allPlayersJson = nlohmann::json::array();
    for (int index = 0; index < players.size(); index++)
    {
        allPlayersJson.push_back(toJson(players[index]));
    }
    if (outFile.is_open())
    {
        outFile << allPlayersJson.dump(4) << std::endl;
    }
    else
    {
        std::cerr << "Ошибка при открытии файла для записи." << std::endl;
    }
}
