#include "map.h"
#include "player.h"
#include "tile.h"
#include <random>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <iostream>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

std::vector<MapSection *> Map::getSections() const
{
    return sections;
}



Map::Map(MapSection *defaultSection,
         std::vector<TileSet *, std::allocator<TileSet *> > *availableTileSets)
{
    // add the first/default section of the map

    this->actuallyLoadedTiles = new std::vector<Tile*>();
    this->nearbyTiles=  std::map<std::pair<int, int>, Tile *>();

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

/**
    // Player coordinates
    double xPlayer = (double) (getItsPlayer()->getAnimation()->x()) / 32;
    double yPlayer = (double) (getScene()->height() - getItsPlayer()->getAnimation()->y()) / 32;

    // Search distance
    int k = 5;
    **/
std::map<std::pair<int, int>, Tile*> Map::collectNearbyTiles(std::vector<Tile*>* tiles, int proximity, double predictedX, double predictedY)
{
    std::map<std::pair<int, int>, Tile*> nearbyTiles;

    // Perform wide search of nearby tiles
    std::queue<Tile*> tileQueue;
    Tile* initialTile = getTileAtCoordinates((int)(predictedX), (int)(predictedY));
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
        if (std::abs(predictedX - currentTile->getX()) >= proximity || std::abs(predictedY - currentTile->getY()) >= proximity)
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
    setNearbyTiles(nearbyTiles);
    return nearbyTiles;
}

//setNearbyTiles(nearbyTiles);
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
}

void Map::displayAnimation() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distW(0, mapView->viewport()->width()); // distribution in range of width
    std::uniform_int_distribution<std::mt19937::result_type> distH(0, mapView->viewport()->height()); // distribution in range of height

    for(int i = 0; i < 4; i++) {
         GifItem *gifItem = new GifItem(":/particules/sprites/particules/fireworks.gif");
         QPointF randPos = mapView->mapToScene(distW(rng), distH(rng));
         gifItem->setPos(randPos);
         this->getScene()->addItem(gifItem);
    }

    QPixmap originalPixmap(":/userInterface/sprites/userInterface/ribbon.png");
    QPixmap ribbonPixmap = originalPixmap.scaled(originalPixmap.width() * 4, originalPixmap.height() * 4);

    QGraphicsPixmapItem *ribbon = new QGraphicsPixmapItem(ribbonPixmap);

    int x = (mapView->viewport()->width() - ribbonPixmap.width()) / 2;
    int y = 200;
    QPointF ribbonPos = mapView->mapToScene(x, y);
    ribbon->setPos(ribbonPos);

    QTransform transform;
    transform.translate(ribbonPixmap.width() / 2, ribbonPixmap.height() / 2);
    transform.rotate(180);
    transform.translate(-ribbonPixmap.width() / 2, -ribbonPixmap.height() / 2);
    ribbon->setTransform(transform);

    this->getScene()->addItem(ribbon);

    QPixmap woodboardPixmap(":/userInterface/sprites/userInterface/woodboard.png");

    QGraphicsPixmapItem *woodboardItem = new QGraphicsPixmapItem(woodboardPixmap);

    woodboardItem->setPos(mapView->viewport()->width(), 0);
    woodboardItem->setVisible(false);

    QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(lcdCount));

    QFont font;
    font.setPointSize(20);
    textItem->setFont(font);

    woodboardPixmap = woodboardPixmap.scaled(textItem->boundingRect().width() + 20, textItem->boundingRect().height() + 20);
    woodboardItem->setPixmap(woodboardPixmap);

    int textX = (mapView->viewport()->width() - textItem->boundingRect().width()) / 2;
    int textY = 60 + ribbonPixmap.height();

    QPointF textPos = mapView->mapToScene(textX, textY);
    textItem->setPos(textPos);
    textItem->setVisible(false);

    woodboardItem->setPos(textItem->pos().x() - 10, textItem->pos().y() - 10);

    this->getScene()->addItem(woodboardItem);

    this->getScene()->addItem(textItem);

    QTimeLine *timeLine = new QTimeLine(2000);
    timeLine->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(ribbon);
    animation->setTimeLine(timeLine);

    for (int i = 0; i <= 100; ++i) {
        animation->setScaleAt(i / 100.0, i / 100.0, i / 100.0);
    }

    timeLine->start();

    AnimationHelper *woodboardHelper = new AnimationHelper(woodboardItem);

    QPropertyAnimation *woodboardAnimation = new QPropertyAnimation(woodboardHelper, "pos");
    woodboardAnimation->setDuration(1000);
    woodboardAnimation->setStartValue(QPointF(textItem->pos().x() - 10, -woodboardPixmap.height()));
    woodboardAnimation->setEndValue(QPointF(textItem->pos().x() - 10, textItem->pos().y() - 10));
    woodboardAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // Create a AnimationHelper for the textItem
    AnimationHelper *textItemHelper = new AnimationHelper(textItem);

    // Create a QPropertyAnimation for the textItem sliding effect
    QPropertyAnimation *textItemAnimation = new QPropertyAnimation(textItemHelper, "pos");
    textItemAnimation->setDuration(1000);
    textItemAnimation->setStartValue(QPointF(textItem->pos().x(), -textItem->boundingRect().height()));
    textItemAnimation->setEndValue(QPointF(textItem->pos().x(), textItem->pos().y()));
    textItemAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    QObject::connect(timeLine, &QTimeLine::finished, [=]() {
        woodboardItem->setVisible(true);
        textItem->setVisible(true);
        woodboardAnimation->start();
        textItemAnimation->start();
    });

    QObject::connect(woodboardAnimation, &QPropertyAnimation::finished, woodboardAnimation, &QPropertyAnimation::deleteLater);
    QObject::connect(textItemAnimation, &QPropertyAnimation::finished, textItemAnimation, &QPropertyAnimation::deleteLater);

    this->getScene()->addItem(woodboardItem);

    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    mediaPlayer->setSource(QUrl("qrc:/sounds/sprites/sounds/levelFinished.mp3"));
    mediaPlayer->play();

    QMediaPlayer *mediaPlayer2 = new QMediaPlayer;
    mediaPlayer2->setSource(QUrl("qrc:/sounds/sprites/sounds/fireworks.mp3"));
    mediaPlayer2->play();
}



void Map::setLcdCount(const std::string &value) {
    lcdCount = value;
}
