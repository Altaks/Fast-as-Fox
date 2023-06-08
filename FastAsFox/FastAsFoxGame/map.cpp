#include "map.h"
#include "tile.h"

std::vector<Tile *> *Map::getActuallyLoadedTiles() const
{
    return actuallyLoadedTiles;
}

Map::Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets)
{
    // add the first/default section of the map

    this->actuallyLoadedTiles = new std::vector<Tile*>();

    this->sections = std::vector<MapSection*>();
    this->sections.push_back(defaultSection);

    // inject every tile from all the tilesets to the map used tiles
    this->loadedTiles = std::map<int, QPixmap*>();
    this->tileSets = new std::vector<TileSet*>();

    this->tileSets->reserve(availableTileSets->size());
    this->tileSets = availableTileSets;

    QPixmap * nullPixmap = new QPixmap(32, 32);
    nullPixmap->fill(Qt::transparent);

    this->loadedTiles.emplace(0, nullPixmap);

    for(TileSet * tileset : *availableTileSets){
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
    tileSets->clear();
}

std::vector<MapSection *>* Map::getMap(){
    return &this->sections;
}

QGraphicsScene * Map::getScene(){
    if(this->mapScene == nullptr){
        this->mapScene = new QGraphicsScene(nullptr);
    }
    return this->mapScene;
}

QGraphicsView * Map::getView(){
    if(this->mapView == nullptr){
        // Create the QGraphicsView & QGraphicsScene
        this->mapView = new QGraphicsView();
        this->mapView->setScene(this->getScene());
    }
    return this->mapView;
}

void Map::load(){

    qDebug(("Index de tile max : " + std::to_string(this->loadedTiles.size())).c_str());

    // inject map at coordinates
    int anchorX = 0;
    for(uint sectionId = 0; sectionId < this->sections.size(); sectionId++){
        MapSection* section = this->sections.at(sectionId);

        // for each tile entry: x ,  y  : tileid
        for(std::map<std::pair<int, int>, int>::iterator tileCoord = section->getCoordinatesToTileId()->begin(); tileCoord != section->getCoordinatesToTileId()->end(); tileCoord++){

            int graphicsX = anchorX + tileCoord->first.first;
            int graphicsY = section->getSectionHeight() - tileCoord->first.second;

            // adapt the coordinates to displayable coordinates
            graphicsX *= 32;
            graphicsY *= 32;

            // apply the texture to the tile
            int tileID = tileCoord->second;
            if(tileID >= this->loadedTiles.size() || tileID < 0) tileID = 0; // set @ null if tile not found

            qDebug(("Id de la tile : " + std::to_string(tileID)).c_str());
            QPixmap * correspondingTexture = this->loadedTiles.at(tileID);

            Tile * correspondingTile = new Tile(correspondingTexture, tileID, anchorX - tileCoord->first.first, tileCoord->first.second);

            // place the tile in the scene
            QGraphicsPixmapItem * tileItem = correspondingTile->getTileItem();
            tileItem->setPos(graphicsX, graphicsY);

            // add the item to the scene
            this->getScene()->addItem(correspondingTile->getTileItem());
            this->actuallyLoadedTiles->push_back(correspondingTile);
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
