#include "prisonController.hpp"
#include "playerController.hpp"

prisonController::prisonController(Prison *prison):prison(prison){}

void prisonController::playerReleaseFromJail(Player *player){
    std::map<Player *, uint8_t> list = prison->getPrisonList();
    std::map<Player *,uint8_t>::iterator it;
    it = list.find(player);
    list.erase(it);
}
bool prisonController::isInJail(Player* player){
    //std::map<Player *,uint8_t> list = prison->getPrisonList();
    for (const auto& pair : prison->getPrisonList()) {
        if (pair.first == player) {
            return pair.second > 0;
        }
    }
    return false;
    // std::map<Player *,uint8_t>::iterator it;
    // return (list.find(player) == nullptr);
}
void prisonController::payToExit(Player* player){
    int fee = prison -> getJailFee();
    if(playerController::playerCanAfford(fee, player) == playerController:: CAN_AFFORD){
        playerController::playerPay(fee, player);
        //FIXME написать что он заплатил и вышел из тюрьмы
        return;
    }
    else if(playerController::playerCanAfford(fee, player) == playerController::CANNOT_AFFORD){
        //FIXME написать что он у него не хватает денег
        return;
    }
}

void prisonController::addPlayerInPrison(Player *player, Prison *prison){
    prison->getPrisonList().insert({player, 1});
}