#ifndef TILE_H
#define TILE_H
#include <QGraphicsPixmapItem>
#include "gameobject.h"

class Tile : public GameObject
{
private:
    /**
     * @brief texture the texture of the tile
     */
    QPixmap * texture;

    /**
     * @brief tile the final item that will be added to the scene
     */
    QGraphicsPixmapItem * tile;

    /**
     * @brief tileid the Id of the tile
     */
    int tileid;

    /// The coordinates of the tile
    int x;
    int y;

    /// Pointers towards nearby tiles
    Tile * upTile = nullptr;
    Tile * bottomTile = nullptr;
    Tile * leftTile = nullptr;
    Tile * rightTile = nullptr;


public:
    explicit Tile(QPixmap * texture, int tileid, int x, int y, QObject *parent = nullptr);
    QGraphicsPixmapItem * getTileItem();
    int getTileId() const;
    int getX() const;
    int getY() const;
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
