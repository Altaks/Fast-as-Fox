#ifndef POWERUP_H
#define POWERUP_H

#include "berry.h"


class PowerUp : public Berry
{
private:
    Level * level= nullptr;
public:
    PowerUp(QGraphicsScene * theScene, Level * levels);
    ~PowerUp();
    void onCollide(GameObject* obj);
    void applyEffect(Player * player);
};

#endif // POWERUP_H
