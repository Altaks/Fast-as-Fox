#ifndef BERRY_H
#define BERRY_H

#include "gameobject.h"
#include "constants.h"

#include <QPixmap>

class Berry : public GameObject
{
protected:
    PowerUpType powerUpType;
    int X;
    int y;
    QPixmap * Sprite;
public:
    Berry();
    int getRandom();
    virtual void onCollide();
    virtual void applyEffect()=0;
};

#endif // BERRY_H
