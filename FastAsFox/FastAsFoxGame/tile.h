#ifndef TILE_H
#define TILE_H
#include <QGraphicsPixmapItem>
#include "gameobject.h"

class Tile : public GameObject
{
private:
    QPixmap * texture;
    QGraphicsPixmapItem * tile;
    int tileId;
    int x;
    int y;

public:
    explicit Tile(QPixmap * texture, int tileId, int x, int y, QObject *parent = nullptr);
    QGraphicsPixmapItem * getTileItem();
    int getTileId() const;
};

#endif // TILE_H
