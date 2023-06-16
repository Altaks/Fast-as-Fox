#include "tile.h"

int Tile::getTileId() const
{
    return tileid;
}

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

Tile *Tile::getUpTile() const
{
    return upTile;
}

void Tile::setUpTile(Tile *newUpTile)
{
    upTile = newUpTile;
}

Tile *Tile::getBottomTile() const
{
    return bottomTile;
}

void Tile::setBottomTile(Tile *newBottomTile)
{
    bottomTile = newBottomTile;
}

Tile *Tile::getLeftTile() const
{
    return leftTile;
}

void Tile::setLeftTile(Tile *newLeftTile)
{
    leftTile = newLeftTile;
}

Tile *Tile::getRightTile() const
{
    return rightTile;
}

void Tile::setRightTile(Tile *newRightTile)
{
    rightTile = newRightTile;
}


Tile::Tile(QPixmap *texture, int tileId, int x, int y, QObject *parent) : GameObject{parent}

{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileid = tileId;
    this->x = x;
    this->y = y;
}

bool Tile::getIsCollideable()
{
    return isCollideable;
}

void Tile::setIsCollideable(bool collideable)
{
    isCollideable = collideable;
}


QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}
