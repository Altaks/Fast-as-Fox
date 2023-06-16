#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>

#include <map>

class TileSet
{
private:
    int startingIndex;
    std::map<int, QPixmap*>* tiles = nullptr;
    std::map<int, QPixmap*>* split();
    std::string filepath;
    int sideSize;
    /**
         * @brief isCollideable boolean that determines if the tiles of the tileset are collideable
         */
        bool isCollideable;

public:
    /**
     * @brief TileSet the constructor for the TileSet class
     * @param filepath the path to the file containing the tileset
     * @param sideSize the size of a side of the tileMap
     * @param startingIndex the index at the beginning of the tileset
     */
    TileSet(std::string filepath, bool collideable, int sideSize, int startingIndex);
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
    /**
     * @brief getIsCollideable getter for isCollideable
     * @return isCollideable
     */
    bool getIsCollideable();

};

#endif // TILESET_H
