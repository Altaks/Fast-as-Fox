#ifndef BERRY_H
#define BERRY_H

#include <QRect>
#include <QGraphicsPixmapItem>

#include "player.h"
#include "animatedsprite.h"
#include "poweruptype.h"
#include "level.h"

class Berry : public QGraphicsPixmapItem
{
protected:
    bool hasBeenUsed = false;
    QPixmap * texture = nullptr;
    QGraphicsScene * scene = nullptr;
public:
    Berry(QGraphicsScene * scene);
    virtual void onCollide(Player * fox);
    virtual void applyEffect(Level * level, Player * fox);
    static Berry * generateRandom(QGraphicsScene * scene, std::pair<int, int> spawnpoint);
    static QPixmap * queryPixmap(PowerUpType type);

    QPixmap *getTexture() const;
    QGraphicsScene *getScene() const;
    void setTexture(QPixmap *newTexture);
    void setScene(QGraphicsScene *newScene);
};

#endif // BERRY_H
