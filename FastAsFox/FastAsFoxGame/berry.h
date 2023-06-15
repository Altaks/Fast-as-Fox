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
    GameObject *  berries= nullptr;
    PowerUpType powerUpType;
    int x=0;
    int y=0;
    QPixmap * BerriesSprite= nullptr;
    QGraphicsScene * theScene= nullptr;
public:
    Berry();
    int generateRandom();
    virtual void onCollide(Player *player);
    virtual void applyEffect(Player * player)=0;
    PowerUpType getPowerUpType();
};

#endif // BERRY_H
