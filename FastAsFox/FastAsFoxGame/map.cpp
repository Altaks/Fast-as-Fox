#include "map.h"
#include "player.h"
#include "tile.h"



Map::Map(MapSection *defaultSection,
         std::vector<TileSet *, std::allocator<TileSet *> > *availableTileSets)
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

    //Creates the mapView and hides the scrollbars
    this->mapView = new QGraphicsView();
    this->mapView->setScene(this->getScene());
    this->mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

std::vector<Tile *> * Map::getActuallyLoadedTiles() const
{
    return actuallyLoadedTiles;
}

std::map<std::pair<int, int>, Tile *> Map::getNearbyTiles() const
{
    return nearbyTiles;
}

void Map::setNearbyTiles(const std::map<std::pair<int, int>, Tile *> &newNearbyTiles)
{
    nearbyTiles = newNearbyTiles;
}

Tile *Map::getTileAtCoordinates(int x, int y)
{
    for (Tile *tile : *getActuallyLoadedTiles()) {
        if (tile->getX() == x && tile->getY() == y) {
            return tile; // Found the tile at the specified coordinates
        }
    }

    return nullptr; // No tile found at the specified coordinates
}

std::map<std::pair<int, int>, Tile *> Map::collectNearbyTiles()
{
    // Player coordinates
    double xPlayer = (double) (getItsPlayer()->getAnimation()->x()) / 32;
    double yPlayer = (double) (getScene()->height() - getItsPlayer()->getAnimation()->y()) / 32;

    // Search distance
    int k = 5;

    std::map<std::pair<int, int>, Tile *> nearbyTiles;

    // Perform wide search of nearby tiles
    std::queue<Tile *> tileQueue;
    Tile *initialTile = getTileAtCoordinates((int)(xPlayer), (int)(yPlayer));
    tileQueue.push(initialTile);

    // Marked tiles
    std::set<Tile*> markedTiles;
    markedTiles.insert(initialTile);

    // Perform breadth-first search
    while (!tileQueue.empty())
    {
        Tile* currentTile = tileQueue.front();
        tileQueue.pop();

        // Add current tile to the result
        nearbyTiles[std::make_pair(currentTile->getX(), currentTile->getY())] = currentTile;

        // Check if the search distance is exceeded in either x or y direction
        if (std::abs(xPlayer - currentTile->getX()) >= k || std::abs(yPlayer - currentTile->getY()) >= k)
        {
            break; // Stop the search
        }

        // Check neighboring tiles
        Tile* upperTile = currentTile->getUpperTile();
        if (upperTile && markedTiles.find(upperTile) == markedTiles.end())
        {
            tileQueue.push(upperTile);
            markedTiles.insert(upperTile);
        }

        Tile* bottomTile = currentTile->getBottomTile();
        if (bottomTile && markedTiles.find(bottomTile) == markedTiles.end())
        {
            tileQueue.push(bottomTile);
            markedTiles.insert(bottomTile);
        }

        Tile* leftTile = currentTile->getLeftTile();
        if (leftTile && markedTiles.find(leftTile) == markedTiles.end())
        {
            tileQueue.push(leftTile);
            markedTiles.insert(leftTile);
        }

        Tile* rightTile = currentTile->getRightTile();
        if (rightTile && markedTiles.find(rightTile) == markedTiles.end())
        {
            tileQueue.push(rightTile);
            markedTiles.insert(rightTile);
        }
    }

    return nearbyTiles;
}

void Map::setItsPlayer(Player *player)
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

Player* Map::getItsPlayer(){
    return itsPlayer;
}

void Map::updateView()
{
    QPointF center = this->itsPlayer->getAnimation()->pos();

    center.rx() += mapView->viewport()->width() / 2;

    center.setX(qMin(qMax(center.x(), mapView->viewport()->width() / 2.0),
                     mapScene->sceneRect().width() - mapView->viewport()->width() / 2.0));
    center.setY(qMin(qMax(center.y(), mapView->viewport()->height() / 2.0),
                     mapScene->sceneRect().height() - mapView->viewport()->height() / 2.0));

    float lerpFactor = 0.1f;
    mapView->centerOn(mapView->mapToScene(mapView->viewport()->rect().center()) * (1.0 - lerpFactor)
                      + center * lerpFactor);
    //qInfo("Called update view");
}
