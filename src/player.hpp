
#include <string>
#include <vector>
#include <cstdint>

#pragma once
class Street;
class Property;
class Game;
enum class CellType;

class Player
{
private:
    std::string name;
    int balance;
    int position;
    std::vector<Property *> listOfProperty;
    bool inJail;// перемистить в Prison
    bool bankrupt;
    int totalPriceOfProperty;
    int totalDiceRoll;
    uint8_t numMovesInPrison;

public:


    enum AffordStatus
    {
        CAN_AFFORD,
        NEED_TO_SELL_PROPERTY,
        CANNOT_AFFORD
    };

    Player(std::string name);
    Player();
    void setInJael(bool flag); //????????????????????????
    void makeMove(int steps);
    void setPosition(int pos);
    void addProperty(Property *property);
    void pay(int amount);
    void receive(int amount);
    AffordStatus canAfford(int amount);
    void mortgageProperty(Property *property);
    void unmortgagedProperty(Property *property);
    int getBalance() const;
    int getTotalPriceOfProperty();
    void buy(Property *property);
    //CellType getCellTypeInListOfProperty(int index);
    std::string getName() const;
    int getPosition() const;
    const std::vector<Property *> &getProperties() const;
    int getQuantityOfProperty();
    bool isBankrupt() const;
    bool isInJail() const;
    void sendToJail();
    void releaseFromJail();
    bool canBuildOn(Property *property) const;
    void buildStructure(Street *property);
    void destroyStructure(Street *street);
    int getNumMovesInPrison();
    void incrementNumMovesInPrison();
    void declareBankruptcy(Player *creditor = nullptr);
    int makeDecision();
    void startAuction(Property *property, const std::vector<Player *> &players);
    void moveToNearestStation(Game *game, int posIndex);
    int getNumberOfHouses() const;
    int getNumberOfHotels() const;
    int getOwnedPropertyCount(CellType type);
    int getLastDiceRoll();
    void setDiceRoll(Game *game);
    void payToExit(int jailFee);
    ~Player();
};