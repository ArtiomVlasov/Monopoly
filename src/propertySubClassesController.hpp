#pragma once
#include "propertySubClasses.hpp"
#include <iostream>
#include "propertyController.hpp"

class Player;
class Property;

class StreetController : public PropertyController
{
private:
    Street *street;

public:
    StreetController(Street *street);
    int handleStreetType(Street::Color color);
    bool isFullListOfStreet(const Player *player, Street::Color color);
    void buildNewHouse();
    void demolishHouse();
    int getBuildingCost();
    // static int calculateRent(Player *player, Street *street);
    int getTotalRent(ArgsForDefAct *args) override;
};

class RailwayController : public PropertyController
{
private:
    Railway *railway;

public:
    RailwayController(Railway *railway);
    // static int calculateRent(Player *player, Railway *street);
    int getTotalRent(ArgsForDefAct *args) override;
};

class UtilitiesController : public PropertyController
{
private:
    Utilities *utilities;

public:
    UtilitiesController(Utilities *utilities);
    // static int calculateRent(Player *player, Utilities *street);
    int getTotalRent(ArgsForDefAct *args) override;
};
