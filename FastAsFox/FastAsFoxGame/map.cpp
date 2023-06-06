#include "map.h"
#include "tile.h"


Map::Map(MapSection * defaultSection, std::vector<TileSet*> availableTileSets)
{
    // add the first/default section of the map

    this->sections = std::vector<MapSection*>();
    this->sections.push_back(defaultSection);

    // Create the QGraphicsView & QGraphicsScene

    this->mapScene = new QGraphicsScene();
    this->mapView = new QGraphicsView();
    this->mapView->setScene(this->mapScene);

    // inject every tile from all the tilesets to the map used tiles
    for(TileSet * tileset : availableTileSets){
        std::map<int, QPixmap*>* tilesFromTileSet = tileset->load();
        for(std::map<int, QPixmap*>::iterator it = tilesFromTileSet->begin(); it != tilesFromTileSet->end(); it++){
            this->loadedTiles.emplace(*it);
        }
    }
}


Map::~Map(){
    delete mapScene;
    delete mapView;

    loadedTiles.clear();
    sections.clear();
    tileSets.clear();
}

std::vector<MapSection *>* Map::getMap(){
    return &this->sections;
}

QGraphicsScene * Map::getScene(){
    return this->mapScene;
}

QGraphicsView * Map::getView(){
    return this->mapView;
}

void Map::load(){
    // inject map at coordinates
    int anchorX = 0;
    for(uint sectionId = 0; sectionId < this->sections.size(); sectionId++){
        MapSection* section = this->sections.at(sectionId);

        // for each tile entry: x ,  y  : tileid
        for(std::map<std::pair<int, int>, int>::iterator tileCoord = section->getCoordinatesToTileId().begin(); tileCoord != section->getCoordinatesToTileId().end(); tileCoord++){

            int graphicsX = anchorX + tileCoord->first.first;
            int graphicsY = section->getSectionHeight() - tileCoord->first.second;

            // adapt the coordinates to displayable coordinates
            graphicsX *= 32;
            graphicsY *= 32;

            // apply the texture to the tile
            QPixmap * correspondingTexture = this->loadedTiles.at(tileCoord->second);
            Tile * correspondingTile = new Tile(correspondingTexture, tileCoord->second);

            // place the tile in the scene
            QGraphicsPixmapItem * tileItem = correspondingTile->getTileItem();
            tileItem->setPos(graphicsX, graphicsY);

            // add the item to the scene
            this->mapScene->addItem(correspondingTile->getTileItem());

        }

        anchorX += section->getSectionWidth();
    }
}

void Map::updateView(GameObject *obj)
{
    QPointF center = obj->getRectangle().center();

    center.rx() += mapView->viewport()->width() / 2;

    center.setX(qMin(qMax(center.x(), mapView->viewport()->width() / 2.0),
                     mapScene->sceneRect().width() - mapView->viewport()->width() / 2.0));
    center.setY(qMin(qMax(center.y(), mapView->viewport()->height() / 2.0),
                     mapScene->sceneRect().height() - mapView->viewport()->height() / 2.0));

    float lerpFactor = 0.1f;
    mapView->centerOn(mapView->mapToScene(mapView->viewport()->rect().center()) * (1.0 - lerpFactor)
                      + center * lerpFactor);
}
