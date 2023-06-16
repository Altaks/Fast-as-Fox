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
    bool isCollideable;
    Tile * upTile = nullptr;
    Tile * bottomTile = nullptr;
    Tile * leftTile = nullptr;
    Tile * rightTile = nullptr;


public:
    explicit Tile(QPixmap * texture, int tileId, int x, int y, QObject *parent = nullptr);
    QGraphicsPixmapItem * getTileItem();
    int getTileId() const;
    int getX() const;
    int getY() const;
    bool getIsCollideable();
    void setIsCollideable(bool collideable);
    Tile *getUpTile() const;
    void setUpTile(Tile *newUpTile);
    Tile *getBottomTile() const;
    void setBottomTile(Tile *newBottomTile);
    Tile *getLeftTile() const;
    void setLeftTile(Tile *newLeftTile);
    Tile *getRightTile() const;
    void setRightTile(Tile *newRightTile);

};

#endif // TILE_H
