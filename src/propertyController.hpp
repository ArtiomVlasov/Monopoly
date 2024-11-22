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
     void unMortgageProperty(Player* player, prisonController *prisonCtrl);
    bool isOwnedProperty();
    static int calculateMortgage(Property *Property);
     int calculateUnMortgage();
    static void markAsAvailable(Property *property);
    //bool isMortgaged(Property *property);
    static int getTotalPriceOfProperty(Player* player);
};