#include <string>
#include <vector>
#include "classes.hpp"

class Player
{
private:
    std::string name;
    int balance;
    int position;
    std::vector<Property> listOfProperty;
    bool inJael;
    bool bankrupt;

public:
    Player(std::string name);
    void makeMove(int steps);
    void addProperty(Property *property);
    void pay(int amount);
    void receive(int amount);
    bool canAfford(int amount) const;
    void mortgageProperty(Property *property);
    void unmortgagedProperty(Property *property);
    int getBalance() const;
    std::string getName() const;
    int getPosition() const;
    const std::vector<Property *> &getProperties() const;
    bool isBankrupt() const;
    bool isInJail() const;
    void sendToJail();
    void releaseFromJail();
    bool canBuildOn(Property *property) const;
    void buildStructure(Property *property);   
    ~Player();
};