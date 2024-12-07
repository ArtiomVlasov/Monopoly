#ifndef DESERIALIZEJSON_HPP
#define DESERIALIZEJSON_HPP
#pragma once
#include <string>
#include <nlohmann/json.hpp>
class Player;

nlohmann::json toJson(Player *player); 
std::vector<Player*> fromJson(std::ifstream& outFile);
nlohmann::json addPlayers(std::vector<Player *> players, std::ofstream& outFile);
#endif
