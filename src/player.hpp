#include <string>
#include <list>
#include "property.hpp"

class Player
{
private:
    std::string name;
    int balance;
    int position;
    std::list<Property> listOfProperty;
public:
    Player();
    void makeMove(int prevPos);
    ~Player();
};