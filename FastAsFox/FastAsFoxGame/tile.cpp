#include "tile.h"

int Tile::getTileId() const
{
    return tileId;
}

Tile::Tile(QPixmap *texture, int tileid, QObject *parent) : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileId = tileid;
}

QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}
