#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "gameobject.h"

/**
 * @brief The Tile class represents a tile in the game.
 *
 * The Tile class encapsulates the properties and functionality of a tile
 * object, including its texture and tile ID.
 */
class Tile : public GameObject
{
    Q_OBJECT

private:
    QPixmap *texture; /**< The texture of the tile. */
    QGraphicsPixmapItem *tile; /**< The graphical representation of the tile. */
    int tileId; /**< The ID of the tile. */
    int x;
    int y;
public:
    /**
     * @brief Constructs a Tile object with the specified texture and tile ID.
     * @param texture The texture of the tile.
     * @param tileId The ID of the tile.
     * @param parent The parent object.
     */
    Tile(QPixmap *texture, int tileid, int x, int y, QObject *parent = nullptr);

    /**
     * @brief Returns the ID of the tile.
     * @return The ID of the tile.
     */
    int getTileId() const;

    /**
     * @brief Returns the graphical representation of the tile.
     * @return The QGraphicsPixmapItem representing the tile.
     */
    QGraphicsPixmapItem *getTileItem();
};

#endif // TILE_H
