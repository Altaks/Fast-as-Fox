#include "tile.h"

int Tile::getTileId() const
{
    return tileId;
}

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

bool Tile::getIsCollideable()
{
    return isCollideable;
}

Tile::Tile(QPixmap *texture, int tileId, int x, int y, bool collideable, QObject *parent) : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileId = tileId;
    this->x = x;
    this->y = y;
    this->isCollideable = collideable;
}

QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}
