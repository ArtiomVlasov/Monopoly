#include "player.hpp"
#include "property.hpp"
#include "../json.hpp"

static Player *fromJson(const nlohmann::json &j, std::vector<Player *> &players)
{
    std::string name = j["name"];
    int balance = j["balance"];
    int position = j["position"];
    Player *player = new Player(name);
    player->setBalance(balance);
    player->setPosition(position);
    for (const auto &propJson : j["listOfProperty"])
    {
        CellType type = propJson["type"];
        std::string propertyName = propJson["name"];
        int price = propJson["price"];
        int rent = propJson["rent"];

        Player *owner = nullptr;
        if (!propJson["owner"].is_null())
        {
            std::string ownerName = propJson["owner"];
            for (auto p : players)
            {
                if (p->getName() == ownerName)
                {
                    owner = p;
                    break;
                }
            }
        }
        Property *property = new Property(type, propertyName, price, rent, owner);
        std::vector<Property *> list = player->getListOfProperty();
        list.push_back(property);
    }

    return player;
}

nlohmann::json toJson(Player *player)
{
    nlohmann::json j;
    j["name"] = player->getName();
    j["balance"] = player->getBalance();
    j["position"] = player->getPosition();
    std::vector<Property *> list = player->getListOfProperty();
    for (const auto &property : list)
    {
        nlohmann::json propJson;
        propJson["name"] = property->getName();
        propJson["price"] = property->getPrice();
        propJson["rent"] = property->getRent();
        propJson["isMortgage"] = property->isMortgaged();

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
    return j;
}