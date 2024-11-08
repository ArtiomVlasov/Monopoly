#include <string>
#include <vector>


class Property;

class Street;

class Player
{
private:
    std::string name;
    int balance;
    int position;
    bool inJael;
    bool bankrupt;
    std::vector<Property> listOfProperty;
public:
    Player(std::string name);
    Player();
    void makeMove(int steps);
    void addProperty(Property &property);
    void pay(int amount);
    void receive(int amount);
    bool canAfford(int amount) const;
    void mortgageProperty(Property &property);
    void unmortgagedProperty(Property &property);
    int getBalance() const;
    std::string getName() const;
    int getPosition() const;
    const std::vector<Property> &getProperties() const;
    bool isBankrupt() const;
    bool isInJail() const;
    void sendToJail();
    void releaseFromJail();
    bool canBuildOn(Property &property) const;
    void buildStructure(Street &property); 
    void destroyStructure(Street &property);   
    ~Player();
};
