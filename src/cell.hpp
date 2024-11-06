#include "player.hpp"

class Cell
{
 public:
    virtual void onLand() = 0;// сообщает на какую клетку попал
    virtual void applyEffect(Player& player) = 0;
    virtual ~Cell() = default;  
};
