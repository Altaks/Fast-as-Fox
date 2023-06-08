#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameobject.h"
//#include "player.h"
#include "tileset.h"
#include "mapsection.h"
#include "tile.h"

class Map
{
private:
    QGraphicsScene * mapScene = nullptr;
    QGraphicsView * mapView = nullptr;
    std::vector<MapSection *> sections;
    std::vector<TileSet *> * tileSets;
    std::map<int, QPixmap*> loadedTiles;
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;
    //Player* itsPlayer;
public:
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    void load();
    std::vector<MapSection *>* getMap();
    QGraphicsScene * getScene();
    QGraphicsView * getView();
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    //Player* getItsPlayer();
private slots:
    void updateView();
};

#endif // MAP_H
