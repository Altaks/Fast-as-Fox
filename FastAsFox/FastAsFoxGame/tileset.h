#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>

#include <map>

class TileSet
{
private:
    /**
     * @brief startingIndex the ID of the first tile of this tileset
     */
    int startingIndex;

    /**
     * @brief tiles the available tiles texture of this tileset
     */
    std::map<int, QPixmap*>* tiles = nullptr;

    /**
     * @brief split produces an image processing that splits the tileset image into tiles textures
     * @return
     */
    std::map<int, QPixmap*>* split();

    /**
     * @brief filepath the file path towards the tileset texture
     */
    std::string filepath;

    /**
     * @brief sideSize the size of the tiles in pixels
     */
    int sideSize;
public:
    /**
     * @brief TileSet a constructor
     * @param filepath the file path towards the tileset texture
     * @param sideSize the size of the tiles in pixels
     * @param startingIndex the ID of the first tile of this tileset
     */
    TileSet(std::string filepath, int sideSize, int startingIndex);
    TileSet();
    ~TileSet();

    /**
     * @brief load loads and return the tileset map of ids to textures
     * @return a pointer towards a map of IDS to Textures
     */
    std::map<int, QPixmap*>* load();
};

#endif // TILESET_H
