#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "player.hpp"
#include "property.hpp"
#include "propertyController.hpp"



// Функции для отрисовки игрового поля и взаимодействия с игроком
void drawBoard();
void displayPlayerInfo(Player* player, Game* game, prisonController *prisonCntl);
void RenderCreateCell(std::string s, int flag);
void displayMenu();
void WelcomeThePlayers(std::vector<Player*> players);
void renderPayPlayer(Player* player, int amount);
void renderReceivePlayer(Player* player, int amount);
void renderPlayerDeclareBankruptcy(Player* creditor);
void renderPlayerDeclareBankruptcyIfCreditor(Player* creditor);
void renderPlayerDeclareBankruptcyIfCreditorGetPos(Player* creditor, Property* property);
void propertyToBank();
void renderPlayerCanBuildOn(Player* player, int flag);
void renderPlayerBuildStructure(Street* street, Player* player);
void renderPlayerNotBuildStructure(Street* street);
void renderPlayerDestroyStructure(Street* street, Player* player, int status);
void renderPlayerMakeBid(int currentHighestBid, Player* player, int status, int bid);
void renderPlayerMakeDicision(Player* player);
void renderPlayerErrirMakeDicision();
void rednerPlayerStartAuction(int status, Player* player, Property* property, int highestBid);
void renderEndTurn(Player *player);
void renderpPlayerMortgageProperty(Property* property, Player* player, PropertyController* propCntl);
void renderpPlayerUnmortgageProperty(Property* property, Player* player, PropertyController* propCntl);
void rednerplayerMoveToNearestStation(int status, int position);
void rednerPlayerAfterPRison(std::string name);
void rednerPlayerNoPRison(std::string name);
void renderPayPlater(Player* player, int amount, Property* property);
void printSellChoice();
void printPropertyList(const std::vector<Property*>& properties);
void printBuildHouseChoice();
void printStreetNotFound();
void printHousePurchaseSuccess();
void printHousePurchaseFailure();
void printInvalidChoice();
