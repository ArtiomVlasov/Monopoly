#pragma once
#include "property.hpp"
#include "player.hpp"
#include <iostream>

class prisonController;

class PropertyController {
private:
    Property *property;
public:
    PropertyController(Property *property);
    static void payRent(Player* player, Property *property);
    void mortgageProperty(Player* player);
    void unMortgageProperty(Player* player);
    bool isOwnedProperty();
    static int calculateMortgage(Property *Property);
    static int calculateUnMortgage();
    static void markAsAvailable(Property *property);
    //bool isMortgaged(Property *property);
    static int getTotalPriceOfProperty(Player* player);
    static Property* getProperty();
};
