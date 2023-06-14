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
     * @brief tile the object o the tile
     */
    QGraphicsPixmapItem * tile;
    /**
     * @brief tileid the ID of the tile
     */
    int tileId;
    /**
     * @brief x the horizontal position of the tile
     */
    int x;
    /**
     * @brief y the vertical position of the tile
     */
    int y;
    Tile * upTile = nullptr;
    Tile * bottomTile = nullptr;
    Tile * leftTile = nullptr;
    Tile * rightTile = nullptr;

public:
    /**
     * @brief Tile the constructor for the tile class
     * @param texture the texture of the tile
     * @param tileid the id of the tile
     * @param x the horizontal position of the tile
     * @param y the vertical position of the tile
     * @param parent the parent of the tile object (required for QObects)
     */
    explicit Tile(QPixmap * texture, int tileId, int x, int y, QObject *parent = nullptr);
    /**
     * @brief getTileItem getter for the tile class
     * @return the tile object
     */
    QGraphicsPixmapItem * getTileItem();
    /**
     * @brief getTileId fetter for tileId
     * @return tileId
     */
    int getTileId() const;
    /**
     * @brief getX getter for x
     * @return x
     */
    int getX() const;
    /**
     * @brief getY getter for y
     * @return y
     */
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
