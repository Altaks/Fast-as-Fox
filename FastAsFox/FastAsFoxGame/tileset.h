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
    /**
     * @brief startingIndex the index at the beginning of the tileset
     */
    int startingIndex;
    /**
     * @brief tiles map containing the tiles of the tileset, as well as their ID
     */
    std::map<int, QPixmap*>* tiles = nullptr;
    /**
     * @brief split Splits the tileset to get each tile separately
     * @return map containing the tiles of the tileset, as well as their ID
     */
    std::map<int, QPixmap*>* split();
    /**
     * @brief filepath the path to the file containing the tileset
     */
    std::string filepath;
    /**
     * @brief sideSize the size of a side of the tileMap
     */
    int sideSize;
public:
    /**
     * @brief TileSet the constructor for the TileSet class
     * @param filepath the path to the file containing the tileset
     * @param sideSize the size of a side of the tileMap
     * @param startingIndex the index at the beginning of the tileset
     */
    TileSet(std::string filepath, int sideSize, int startingIndex);
    /**
     * @brief TileSet the default constructor for the TileSet class
     */
    TileSet();

    /**
     * @brief Destructor for the TileSet class.
     */
    ~TileSet();
    /**
     * @brief load loads the tiles in the tileset
     * @return a map containing the sprite of every tile, as well as their ID
     */
    std::map<int, QPixmap*>* load();
};

#endif // TILESET_H
