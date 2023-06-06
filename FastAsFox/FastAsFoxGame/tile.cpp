#include "tile.h"

int Tile::getTileid() const
{
    return tileid;
}

Tile::Tile(QPixmap *texture, int tileid, QObject *parent) : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileid = tileid;
}

QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}

