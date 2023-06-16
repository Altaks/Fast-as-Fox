#ifndef POWERUP_H
#define POWERUP_H

#include "player.h"
#include "berry.h"
#include "poweruptype.h"

class PowerUp : public Berry
{
    PowerUpType type;
public:
    PowerUp(QGraphicsScene * scene, PowerUpType type, std::pair<int, int> spawnpoint);
    void onCollide(Player * player);
    void applyEffect(Level * level, Player * player);
    void addToScene();
};

#endif // POWERUP_H
