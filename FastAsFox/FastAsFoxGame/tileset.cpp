#include "tileset.h"

#include <QFile>

TileSet::TileSet(std::string filepath, int sizeSize, int startingIndex){
    this->startingIndex = startingIndex;
    this->filepath = filepath;
    this->sizeSize = sizeSize;
}

TileSet::~TileSet(){
    delete this->tiles;
}

std::map<int, QPixmap*>* TileSet::load(){
    if(this->tiles == nullptr){
        this->tiles = this->split();
    }
    return this->tiles;
}

std::map<int, QPixmap *>* TileSet::split()
{
    QPixmap tileset = QPixmap(QString::fromStdString(filepath));
    int currentTileIndex = startingIndex;
    for(int tilesetX = 0, tileCoordX = 0; tilesetX < tileset.width(); tilesetX += sizeSize, tileCoordX++){
        for(int tilesetY = 0, tileCoordY = 0; tilesetY < tileset.height(); tilesetY += sizeSize, tileCoordY++){
            QPixmap * fragment = new QPixmap();
            *fragment = tileset.copy(tilesetX, tilesetY, sizeSize, sizeSize);
            this->tiles->emplace(currentTileIndex, fragment);
            currentTileIndex++;
        }
    }
    return this->tiles;
}
