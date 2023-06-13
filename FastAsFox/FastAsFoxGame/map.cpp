#include "map.h"
#include "player.h"
#include "tile.h"

Map::Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets)
{
    // add the first/default section of the map
    this->actuallyLoadedTiles = new std::vector<Tile*>();
    this->toCheckForCollision = new std::set<Tile*>();

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

    //Creates the mapView and hides the scrollbars
    this->mapView = new QGraphicsView();
    this->mapView->setScene(this->getScene());
    this->mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

std::vector<Tile *> *Map::getActuallyLoadedTiles() const
{
    return actuallyLoadedTiles;
}

void Map::setItsPlayer(Player* player)
{
    itsPlayer = player;
    this->connect(itsPlayer, SIGNAL(playerMoved()), this, SLOT(updateView()));
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
    return this->mapView;
}

void Map::load(){

    std::map<std::pair<int, int>, Tile*> coordinatesToTile;

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
            if(this->loadedTiles.find(tileID) == this->loadedTiles.end()) tileID = 0; // set @ null if tile not found

            qDebug() << "Id de la tile : " << std::to_string(tileID) << "\n";
            QPixmap * correspondingTexture = this->loadedTiles.at(tileID);

            Tile * correspondingTile = new Tile(correspondingTexture, tileID, anchorX - tileCoord->first.first, tileCoord->first.second);

            // place the tile in the scene
            QGraphicsPixmapItem * tileItem = correspondingTile->getTileItem();
            tileItem->setPos(graphicsX, graphicsY);

            // add the item to the scene
            this->getScene()->addItem(correspondingTile->getTileItem());
            this->actuallyLoadedTiles->push_back(correspondingTile);
            coordinatesToTile.emplace(std::pair<int, int>(correspondingTile->getX(), correspondingTile->getY()), correspondingTile);
        }

        anchorX += section->getSectionWidth();
    }

    // apply pointers for each tile
    for(Tile * tile : *this->actuallyLoadedTiles){
        if(tile->getTileId() == 0) continue;
        int tileX = tile->getX();
        int tileY = tile->getY();

        std::pair<int, int> upPair       = std::pair<int, int>(tileX, tileY+1);
        std::pair<int, int> bottomPair   = std::pair<int, int>(tileX, tileY-1);
        std::pair<int, int> leftPair     = std::pair<int, int>(tileX-1, tileY);
        std::pair<int, int> rightPair    = std::pair<int, int>(tileX+1, tileY);

        if(coordinatesToTile.find(upPair) != coordinatesToTile.end()){
            tile->setUpTile(coordinatesToTile.at(upPair));
        }
        if(coordinatesToTile.find(bottomPair) != coordinatesToTile.end()){
            tile->setBottomTile(coordinatesToTile.at(bottomPair));
        }
        if(coordinatesToTile.find(leftPair) != coordinatesToTile.end()){
            tile->setLeftTile(coordinatesToTile.at(leftPair));
        }
        if(coordinatesToTile.find(rightPair) != coordinatesToTile.end()){
            tile->setRightTile(coordinatesToTile.at(rightPair));
        }
    }

    // collect all near-air tiles
    for(Tile * tile : *this->actuallyLoadedTiles){

        if(tile->getBottomTile() != nullptr && tile->getBottomTile()->getTileId() == 0){
            this->toCheckForCollision->emplace(tile);
        } else if(tile->getUpTile() != nullptr && tile->getUpTile()->getTileId() == 0){
            this->toCheckForCollision->emplace(tile);
        } else if(tile->getLeftTile() != nullptr && tile->getLeftTile()->getTileId() == 0){
            this->toCheckForCollision->emplace(tile);
        } else if(tile->getRightTile() != nullptr && tile->getRightTile()->getTileId() == 0){
            this->toCheckForCollision->emplace(tile);
        }
    }

    /*
    QPixmap * coll = new QPixmap(32, 32);
    coll->fill(Qt::green);
    for(Tile * tile : *this->toCheckForCollision) tile->getTileItem()->setPixmap(*coll);
    */
    return;
}

Player* Map::getItsPlayer(){
    return itsPlayer;
}

std::set<Tile *> *Map::getToCheckForCollision() const {
    return this->toCheckForCollision;
}

void Map::updateView()
{
    QPointF center = this->itsPlayer->getAnimation()->pos();

    center.rx() += mapView->viewport()->width() / 3;

    center.setX(qMin(qMax(center.x(), mapView->viewport()->width() / 2.0),
                     mapScene->sceneRect().width() - mapView->viewport()->width() / 2.0));
    center.setY(qMin(qMax(center.y(), mapView->viewport()->height() / 3.0),
                     mapScene->sceneRect().height() - mapView->viewport()->height() / 2.0));

    float lerpFactor = 0.1f;
    mapView->centerOn(mapView->mapToScene(mapView->viewport()->rect().center()) * (1 - lerpFactor)
                      + center * lerpFactor);
}
