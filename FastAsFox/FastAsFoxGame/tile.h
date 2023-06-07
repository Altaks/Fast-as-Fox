#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

#include "gameobject.h"

class Tile : public GameObject
{
private:
    QPixmap * texture;
    QGraphicsPixmapItem * tile;
    int tileid;
    int x;
    int y;
public:
    explicit Tile(QPixmap * texture, int tileid,int x, int y, QObject *parent = nullptr);
    QGraphicsPixmapItem * getTileItem();
    int getTileid() const;
};

#endif // TILE_H
