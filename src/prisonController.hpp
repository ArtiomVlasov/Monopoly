#include "TaxPrisonChance.hpp"

class prisonController
{
private:
    Prison *prison;
public:
    prisonController(Prison *prison);
    void playerReleaseFromJail(Player *player);
    bool isInJail(Player* player);
    void payToExit(Player* player);
    static void addPlayerInPrison(Player *player, Prison *prison);
};

