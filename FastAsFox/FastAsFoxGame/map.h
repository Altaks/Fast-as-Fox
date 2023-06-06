#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameobject.h"
#include "tileset.h"
#include "mapsection.h"

class Map
{
private:
    QGraphicsScene * mapScene = nullptr;
    QGraphicsView * mapView = nullptr;
    std::vector<MapSection *> sections;
    std::vector<TileSet *> * tileSets;
    std::map<int, QPixmap*> loadedTiles;
public:
    Map(MapSection * defaultSection, std::vector<TileSet*> * availableTileSets);
    ~Map();
    void load();
    std::vector<MapSection *>* getMap();
    QGraphicsScene * getScene();
    QGraphicsView * getView();
private slots:
    void updateView(GameObject * obj);
};

#endif // MAP_H
