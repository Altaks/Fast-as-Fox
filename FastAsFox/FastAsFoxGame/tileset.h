#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>
#include <map>

/**
 * @brief The TileSet class represents a tileset in the game.
 *
 * The TileSet class manages the loading and splitting of a tileset image into individual tiles.
 */
class TileSet
{
private:
    int startingIndex; /**< The starting index for tile IDs. */
    std::map<int, QPixmap*>* tiles; /**< The map of tile IDs to QPixmap pointers. */
    std::string filepath; /**< The file path of the tileset image. */
    int sideSize; /**< The size (width and height) of each tile in pixels. */

public:
    /**
     * @brief Constructs a TileSet object with the specified tileset image file path, side size, and starting index.
     * @param filepath The file path of the tileset image.
     * @param sideSize The size (width and height) of each tile in pixels.
     * @param startingIndex The starting index for tile IDs.
     */
    TileSet(std::string filepath, int sideSize, int startingIndex);

    /**
     * @brief Default constructor for the TileSet class.
     */
    TileSet();

    /**
     * @brief Destructor for the TileSet class.
     */
    ~TileSet();

    /**
     * @brief Loads and splits the tileset image into individual tiles.
     * @return A map of tile IDs to QPixmap pointers.
     */
    std::map<int, QPixmap*>* load();

private:
    /**
     * @brief Splits the tileset image into individual tiles.
     * @return A map of tile IDs to QPixmap pointers.
     */
    std::map<int, QPixmap*>* split();
};

#endif // TILESET_H
