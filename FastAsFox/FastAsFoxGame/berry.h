#ifndef BERRY_H
#define BERRY_H

#include "gameobject.h"
#include "constants.h"
#include "level.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Berry : public GameObject, public QGraphicsPixmapItem
{
protected:
    GameObject *  berries;
    PowerUpType powerUpType;
    int x;
    int y;
    QPixmap * BerriesSprite;
    QGraphicsScene * theScene;
public:
    Berry();
    int generateRandom();
    virtual void onCollide(Player *player);
    virtual void applyEffect(Player * player)=0;
    PowerUpType getPowerUpType();
};

#endif // BERRY_H
