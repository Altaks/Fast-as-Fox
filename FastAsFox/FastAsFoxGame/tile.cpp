#include "tile.h"

Tile::Tile(QPixmap *texture, QObject *parent) : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
}
