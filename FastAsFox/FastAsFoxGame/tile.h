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
    Tile *upperTile;
    Tile *bottomTile;
    Tile *leftTile;
    Tile *rightTile;

public:
    explicit Tile(QPixmap * texture, int tileid, int x, int y, QObject *parent = nullptr);
    QGraphicsPixmapItem * getTileItem();
    int getTileId() const;
    int getX() const;
    int getY() const;

    Tile *getUpperTile() const;
    Tile *getBottomTile() const;
    Tile *getLeftTile() const;
    Tile *getRightTile() const;
    void setUpperTile(Tile *newUpperTile);
    void setBottomTile(Tile *newBottomTile);
    void setLeftTile(Tile *newLeftTile);
    void setRightTile(Tile *newRightTile);
};

#endif // TILE_H
