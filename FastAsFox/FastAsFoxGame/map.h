#ifndef MAP_H
#define MAP_H

#include <set>
#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameobject.h"
#include "tileset.h"
#include "mapsection.h"
#include "tile.h"
#include <random>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <iostream>
#include <QGraphicsProxyWidget>
#include <QAudioOutput>
#include <QStyle>
#include <QTimeLine>
#include <QPushButton>
#include <QGraphicsItemAnimation>
#include <QCoreApplication>
#include <QApplication>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>

class Level;

class Player; //Forward declaration of player, to avoid creating an circular inclusion, as map.h is already included in player.h

class Map : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene * mapScene = nullptr;
    QGraphicsView * mapView = nullptr;
    std::vector<MapSection *> sections;
    std::vector<TileSet *> * tileSets;
    std::map<int, std::pair<bool, QPixmap*>> loadedTiles;
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;
    std::set<Tile*> * toCheckForCollision = nullptr;
    std::string lcdCount;
    QPushButton *homeButton;
    Player* itsPlayer;
public:
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    void load();
    std::vector<MapSection *>* getMap();
    QGraphicsScene * getScene();
    QGraphicsView * getView();
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    void setItsPlayer(Player* player);
    Player* getItsPlayer();
    std::set<Tile *> * getToCheckForCollision() const;
    std::vector<MapSection *> getSections() const;
    void setLcdCount(const std::string &value);
    void displayAnimation(Level * level);


public slots:
    void updateView();
    void handleLevelMenuButton();

signals:
    void homeButtonClicked();
    void golevelMenu();

};


#endif // MAP_H
