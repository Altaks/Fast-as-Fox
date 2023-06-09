#include "tile.h"

Tile::Tile(QPixmap *texture, int tileid, int x, int y, QObject *parent)
    : GameObject{parent}
{
    this->texture = texture;
    this->tile = new QGraphicsPixmapItem(*texture);
    this->tileid = tileid;
    this->x = x;
    this->y = y;
    this->setUpperTile(nullptr);
    this->setBottomTile(nullptr);
    this->setLeftTile(nullptr);
    this->setRightTile(nullptr);
}

QGraphicsPixmapItem *Tile::getTileItem()
{
    return this->tile;
}

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

Tile *Tile::getUpperTile() const
{
    return upperTile;
}

Tile *Tile::getBottomTile() const
{
    return bottomTile;
}

Tile *Tile::getLeftTile() const
{
    return leftTile;
}

Tile *Tile::getRightTile() const
{
    return rightTile;
}

void Tile::setUpperTile(Tile *newUpperTile)
{
    upperTile = newUpperTile;
}

void Tile::setBottomTile(Tile *newBottomTile)
{
    bottomTile = newBottomTile;
}

void Tile::setLeftTile(Tile *newLeftTile)
{
    leftTile = newLeftTile;
}

void Tile::setRightTile(Tile *newRightTile)
{
    rightTile = newRightTile;
}
