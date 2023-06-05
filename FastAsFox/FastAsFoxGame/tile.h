#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

#include "gameobject.h"

class Tile : public GameObject
{
private:
    QPixmap * texture;
    QGraphicsPixmapItem * tile;
public:
    explicit Tile(QPixmap * texture, QObject *parent = nullptr);
    bool collides(GameObject * obj);
    QGraphicsPixmapItem * getTileItem();
};

#endif // TILE_H
