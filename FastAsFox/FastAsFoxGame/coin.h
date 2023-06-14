#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "gameobject.h"
#include "player.h"
#include "animatedsprite.h"


class Coin : public GameObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    GameObject* coinToCollect;
    QPixmap * texture;
    QGraphicsScene * scene;
    std::pair<int,int> position;//coordinates <x,y>
    int coinCounter;
public:
    Coin(QGraphicsScene * theScene, std::pair<int,int> position, int sectionHeight);
    ~Coin();
    int getX() const;
    int getY() const;
    int getCoinCounter() const;

public slots:
    void handleCollision(Fox* fox);

signals:
    void coinCollected();
};

#endif // COIN_H
