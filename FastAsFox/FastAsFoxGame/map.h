#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QPair>
#include "gameobject.h"
#include "mapsection.h"
#include "tile.h"
#include "tileset.h"
#include <map>
#include <queue>
#include <set>

class Player; //Forward declaration of player, to avoid creating an circular inclusion, as map.h is already included in player.h

class Map : public QObject
{
    Q_OBJECT

private:
    Player *itsPlayer;
    QGraphicsScene * mapScene = nullptr;
    QGraphicsView * mapView = nullptr;
    std::vector<MapSection *> sections;
    std::vector<TileSet *> * tileSets;
    std::map<int, QPixmap*> loadedTiles;
    std::vector<Tile *> *actuallyLoadedTiles = nullptr;
    std::map<std::pair<int, int>, Tile *> nearbyTiles;

public:
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    void load();
    std::vector<MapSection *>* getMap();
    QGraphicsScene * getScene();
    QGraphicsView * getView();
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    void setItsPlayer(Player* player);
    Player *getItsPlayer();
    std::map<std::pair<int, int>, Tile *> getNearbyTiles() const;
    std::map<std::pair<int, int>, Tile*> collectNearbyTiles(std::vector<Tile*>* tiles, int proximity, double predictedX, double predictedY);
    Tile *getTileAtCoordinates(int x, int y);

    void setNearbyTiles(const std::map<std::pair<int, int>, Tile *> &newNearbyTiles);

public slots:
    void updateView();
};

#endif // MAP_H
