#include "TaxPrisonChanceCntl.hpp"
#include "playerController.hpp"
#include "render.hpp"

prisonController::prisonController(Prison *prison) : CellController(prison) {}

void prisonController::playerReleaseFromJail(Player *player)
{
    std::map<Player *, uint8_t> *list = prison->getPlayerPrisonList();
    std::map<Player *, uint8_t>::iterator it;
    it = list->find(player);
    list->erase(it);
}
bool prisonController::isInJail(Player *player)
{
    std::cout<<"______________________\n";
    if(prison == nullptr){
        return false;
    }
    std::map<Player *, uint8_t> *playerPrison = prison->getPlayerPrisonList();
    std::cout<<"+++++++++++++++++++\n";
    if(playerPrison->empty()){
        return false;
    }
    std::cout<<"******************\n";
    auto it = playerPrison->find(player);
    if (it != playerPrison->end())
    {
        return it->second > 0;
    }
    return false;
    // std::map<Player *,uint8_t>::iterator it;
    // return (list.find(player) == nullptr);
}
void prisonController::payToExit(Player *player, playerController *plrCntl)
{
    int fee = prison->getJailFee();
    if (plrCntl->playerCanAfford(fee) == playerController::CAN_AFFORD)
    {
        renderPayPlayer(player, fee);
        player->setBalance(player->getBalance() - fee);
        rednerPlayerAfterPRison(player->getName());
        return;
    }
    else if (plrCntl->playerCanAfford(fee) == playerController::CANNOT_AFFORD)
    {
        rednerPlayerNoPRison(player->getName());
        return;
    }
}

void prisonController::addPlayerInPrison(Player *player)
{
    prison->getPlayerPrisonList()->insert({player, 1});
}

Prison *prisonController::getPrison()
{
    return prison;
}

void prisonController::defaultAction(ArgsForDefAct *args)
{
    std::cout << "Игрок " << args->player->getName() << " отправляется в тюрьму." << std::endl;
    addPlayerInPrison(args->player);
}

TaxController::TaxController(Tax *tax) : CellController(tax) {}

void TaxController::defaultAction(ArgsForDefAct *args)
{
    std::cout << "Игрок " << args->player->getName() << " должен заплатить налог в размере " << tax->getTaxAmount() << " монет." << std::endl;
    playerController::AffordStatus affordStatus = args->plrCntl->playerCanAfford(tax->getTaxAmount());
    if (affordStatus == playerController::AffordStatus::CAN_AFFORD)
    {
        renderPayPlayer(args->player, tax->getTaxAmount());
        args->player->setBalance(args->player->getBalance() - tax->getTaxAmount());
        // playerController::playerPay(tax, player);
    }
    else if (affordStatus == playerController::AffordStatus::NEED_TO_SELL_PROPERTY)
    {
        std::cout << "У игрока " << args->player->getName() << " недостаточно средств на балансе. " << "Необходимо продать имущество для оплаты налога.\n";

        while (args->plrCntl->playerCanAfford(tax->getTaxAmount()) == playerController::AffordStatus::NEED_TO_SELL_PROPERTY)
        {
            args->game->sellProperty(args->player, args->plrCntl); //??????????????????
        }
    }
    else
    {
        std::cout << "У игрока " << args->player->getName() << " недостаточно средств для уплаты налога." << std::endl;
        args->game->addBankruptPlayers(args->player);
    }
}

ChanceController::ChanceController(Chance *chance) : CellController(chance) {}

void ChanceController::defaultAction(ArgsForDefAct *args)
{
    std::cout << "Игрок " << args->player->getName() << " вытягивает карту 'Шанс'." << std::endl; // FIXME докинуть в render
    std::vector<std::function<void(Player *)>> effects = chance->getEffectsList();
    int effectIndex = rand() % effects.size();
    effects[effectIndex](args->player);
}

void PublicTreasuryController::defaultAction(ArgsForDefAct *args)
{
    std::vector<std::function<void(Player *)>> actions = treasure->getEffectsList();
    int effectIndex = rand() % actions.size();
    std::cout << args->player->getName() << " попадает на клетку 'Общественная казна'.\n";
    actions[effectIndex](args->player);
}
PublicTreasuryController::PublicTreasuryController(PublicTreasury *treasure) : CellController(treasure) {}

EmptyCellController::EmptyCellController() : CellController(nullptr) {}

void EmptyCellController::defaultAction(ArgsForDefAct *args) {}
