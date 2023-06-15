#ifndef POWERDOWN_H
#define POWERDOWN_H

#include "berry.h"

#include "powerdowntype.h"

class PowerDown : public Berry
{
    PowerDownType type;
    bool hasBeenPickedUp = false;
public:
    PowerDown(QGraphicsScene * scene, PowerDownType type, std::pair<int, int> spawnpoint);
    void onCollide(Player * player);
    void applyEffect(Level * level, Player * player);
};

#endif // POWERDOWN_H
