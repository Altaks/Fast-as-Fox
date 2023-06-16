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
    /**
     * @brief mapScene a pointer towards the scene where the map is loaded
     */
    QGraphicsScene * mapScene = nullptr;
    /**
     * @brief mapView a pointer towards the view that displays the scene
     */
    QGraphicsView * mapView = nullptr;

    /**
     * @brief sections a vector that contains the loaded map sections
     */
    std::vector<MapSection *> sections;

    /**
     * @brief tileSets a vector that contains the available tilesets for the map to load
     */
    std::vector<TileSet *> * tileSets;

    /**
     * @brief loadedTiles a map that contains the id and the associated texture
     */
    std::map<int, QPixmap*> loadedTiles;

    /**
     * @brief actuallyLoadedTiles the currently loaded tiles in the scene
     */
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;

    /**
     * @brief toCheckForCollision a set that contains pointers towards the tiles to check for terrain collision
     */
    std::set<Tile*> * toCheckForCollision = nullptr;
    std::string lcdCount;
    QPushButton *homeButton;

    /**
     * @brief itsPlayer a pointer towards the player
     */
    Player* itsPlayer;
public:

    /**
     * @brief Map the constructor
     * @param defaultSection the default section that will be loaded
     * @param availableTileSets the available tilesets to get the textures
     */
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();

    /**
     * @brief loads the map to the scene
     */
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
    /**
     * @brief updateView places correctly the camera
     */
    void updateView();
    void handleLevelMenuButton();

signals:
    void homeButtonClicked();
    void golevelMenu();

};


#endif // MAP_H
