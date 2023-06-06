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
public:
    TileSet(std::string filepath, int sideSize, int startingIndex);
    ~TileSet();
    std::map<int, QPixmap*>* load();
};

#endif // TILESET_H
