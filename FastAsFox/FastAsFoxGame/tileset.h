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
    bool isCollideable;

public:
    TileSet(std::string filepath, bool collideable, int sideSize, int startingIndex);
    TileSet();
    ~TileSet();
    std::map<int, QPixmap*>* load();
    bool getIsCollideable();
};

#endif // TILESET_H
