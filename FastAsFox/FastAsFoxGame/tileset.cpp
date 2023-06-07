#include "tileset.h"

#include <QFile>

TileSet::TileSet(std::string filepath, int sideSize, int startingIndex){
    this->startingIndex = startingIndex;
    this->filepath = filepath;
    this->sideSize = sideSize;
    this->tiles = nullptr;
}

TileSet::TileSet(){

}

TileSet::~TileSet(){
    delete this->tiles;
}

std::map<int, QPixmap*>* TileSet::load(){
    if(this->tiles == nullptr){
        this->tiles = new std::map<int, QPixmap*>();
    }
    if(this->tiles->size() == 0){
        this->tiles = this->split();
    }
    return this->tiles;
}

std::map<int, QPixmap *>* TileSet::split()
{
    QPixmap tileset = QPixmap(QString::fromStdString(filepath));
    int currentTileIndex = startingIndex;
    for(int tilesetX = 0, tileCoordX = 0; tilesetX < tileset.width(); tilesetX += sideSize, tileCoordX++){
        for(int tilesetY = 0, tileCoordY = 0; tilesetY < tileset.height(); tilesetY += sideSize, tileCoordY++){
            QPixmap * fragment = new QPixmap();
            *fragment = tileset.copy(tilesetY, tilesetX, sideSize, sideSize);
            this->tiles->emplace(currentTileIndex, fragment);
            currentTileIndex++;
        }
    }
    return this->tiles;
}
