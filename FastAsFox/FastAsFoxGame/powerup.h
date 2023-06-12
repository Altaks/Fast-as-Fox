#ifndef POWERUP_H
#define POWERUP_H

#include "berry.h"
#include "level.h"

class PowerUp : public Berry
{

public:
    PowerUp();
    void onCollide(GameObject* obj);
    void applyEffect(Player * player, Level * level);
};

#endif // POWERUP_H
