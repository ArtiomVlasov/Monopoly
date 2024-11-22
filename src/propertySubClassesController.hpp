#pragma once
#include "property.hpp"
#include "player.hpp"
#include "propertySubClasses.hpp"
#include <iostream>

class StreetController{
private:
    Street *street;
public:
    int handleStreetType(Street::Color color);
     bool isFullListOfStreet(const Player *player, Street::Color color);
     void buildNewHouse();
     void demolishHouse();
    int getBuildingCost();
    static int calculateRent(Player *player, Street *street);
};

class RailwayController{
public:
    static int calculateRent(Player *player, Railway *street);
};

class UtilitiesController{
public:
    static int calculateRent(Player *player, Utilities *street);
};