#pragma once
#include <iostream>
#include "cellController.hpp"

class Player;
class Property;

class prisonController;

class PropertyController : public CellController{
private:
    Property *property;
public:
    PropertyController(Property *property);
     void payRent(ArgsForDefAct *args);
    void mortgageProperty(Player* player);
    void unMortgageProperty(Player* player);
    bool isOwnedProperty();
     int calculateMortgage();
     int calculateUnMortgage();
     void markAsAvailable(Property *property);
    //bool isMortgaged(Property *property);
    // static Property* getProperty();
    void defaultAction(ArgsForDefAct *args) override;
    virtual int getTotalRent(ArgsForDefAct *args) = 0;
};
