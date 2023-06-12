#ifndef BERRY_H
#define BERRY_H

#include "gameobject.h"
#include "constants.h"
#include "player.h"

#include <QPixmap>

class Berry : public GameObject
{
protected:
    PowerUpType powerUpType;
    int X;
    int y;
    QPixmap * BerriesSprite;
public:
    Berry();
    int getRandom();
    virtual void onCollide(GameObject* obj);
    virtual void applyEffect(Player * player)=0;
};

#endif // BERRY_H
