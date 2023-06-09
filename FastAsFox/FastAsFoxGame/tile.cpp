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

Tile::Tile(QPixmap *texture, int tileid, int x, int y, QObject *parent) : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileId = tileid;
    this->x = x;
    this->y = y;
}

QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}
