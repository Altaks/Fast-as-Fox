#include "map.h"
#include "animationhelper.h"
#include "gifitem.h"
#include "levelmenubutton.h"
#include "player.h"
#include "tile.h"

Map::Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets)
{
    // add the first/default section of the map

    this->toCheckForCollision = new std::set<Tile*>();
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
            coordinatesToTile.emplace(std::pair<int, int>(correspondingTile->getX(), correspondingTile->getY()), correspondingTile);

        }

        anchorX += section->getSectionWidth();
    }

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
qDebug() << "Map loaded";
       return;

}

std::set<Tile *> *Map::getToCheckForCollision() const {
       return this->toCheckForCollision;
}

void Map::setLcdCount(const std::string &value) {
       lcdCount = value;
}


Player* Map::getItsPlayer(){
    return itsPlayer;
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

void Map::handleLevelMenuButton()
{
    emit golevelMenu();
}

void Map::displayAnimation() {


    GifItem* fireworks = new GifItem(":/particules/sprites/particules/fireworks.gif");
    fireworks->setPos(mapView->mapToScene(mapView->viewport()->width() / 2, mapView->viewport()->height() / 2));
    this->getScene()->addItem(fireworks);

    QPixmap originalPixmap(":/userInterface/sprites/userInterface/ribbon.png");
    QPixmap ribbonPixmap = originalPixmap.scaled(originalPixmap.width() * 4, originalPixmap.height() * 4);

    QGraphicsPixmapItem *ribbon = new QGraphicsPixmapItem(ribbonPixmap);
    this->getScene()->addItem(ribbon);

    int x = (mapView->viewport()->width() - ribbonPixmap.width()) / 2;
    int y = 200;
    QPointF ribbonPos = mapView->mapToScene(x, y);
    ribbon->setPos(ribbonPos);

    QPixmap woodboardPixmap(":/userInterface/sprites/userInterface/woodboard.png");

    QGraphicsPixmapItem *woodboardItem = new QGraphicsPixmapItem(woodboardPixmap);

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
    animation->setTimeLine(timeLine);

    for (int i = 0; i <= 100; ++i) {
           animation->setScaleAt(i / 100.0, i / 100.0, i / 100.0);
    }
    timeLine->start();

    AnimationHelper *woodboardHelper = new AnimationHelper(woodboardItem);

    QPropertyAnimation *woodboardAnimation = new QPropertyAnimation(woodboardHelper, "pos");
    woodboardAnimation->setDuration(1000);
    woodboardAnimation->setStartValue(QPointF(textItem->pos().x() - 20, -woodboardPixmap.height() + 200));
    woodboardAnimation->setEndValue(QPointF(textItem->pos().x() - 20, textItem->pos().y() - 10));
    woodboardAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // Create a AnimationHelper for the textItem
    AnimationHelper *textItemHelper = new AnimationHelper(textItem);

    // Create a QPropertyAnimation for the textItem sliding effect
    QPropertyAnimation *textItemAnimation = new QPropertyAnimation(textItemHelper, "pos");
    textItemAnimation->setDuration(1000);
    textItemAnimation->setStartValue(QPointF(textItem->pos().x() - 10, -textItem->boundingRect().height() + 200));
    textItemAnimation->setEndValue(QPointF(textItem->pos().x() - 10, textItem->pos().y()));
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
    QAudioOutput *audioOutput = new QAudioOutput;
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->play();

    QMediaPlayer *mediaPlayer2 = new QMediaPlayer;
    mediaPlayer2->setSource(QUrl("qrc:/sounds/sprites/sounds/fireworks.mp3"));
    QAudioOutput *audioOutput2 = new QAudioOutput;
    mediaPlayer2->setAudioOutput(audioOutput2);
    mediaPlayer2->play();

    // load the icon
    QPixmap homeButtonPixmap(":/userInterface/sprites/userInterface/homeButton.png");

    // reduce the size of the pixmap by 2
    QPixmap scaledPixmap = homeButtonPixmap.scaled(homeButtonPixmap.size() / 2);

    // create the button
    LevelMenuButton *homeButton = new LevelMenuButton(scaledPixmap);
    this->getScene()->addItem(homeButton);

    // position the button at the bottom of the woodboard
    QPointF buttonPos = woodboardItem->pos();
    buttonPos.setY(buttonPos.y() + woodboardPixmap.height()+30);
    homeButton->setPos(buttonPos);
    QObject::connect(homeButton, &LevelMenuButton::golevelMenu, this, &Map::handleLevelMenuButton);


}


