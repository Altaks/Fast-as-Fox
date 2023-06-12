#ifndef POWERUP_H
#define POWERUP_H

#include "berry.h"


class PowerUp : public Berry
{
public:
    PowerUp();
    void onCollide();
    void applyEffect();
};

#endif // POWERUP_H
