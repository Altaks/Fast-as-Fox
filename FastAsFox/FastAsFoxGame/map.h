#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameobject.h"
#include "tileset.h"
#include "mapsection.h"
#include "tile.h"

class Player; //Forward declaration of player, to avoid creating an circular inclusion, as map.h is already included in player.h



class Map : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief mapScene the scene that contains every object in the game
     */
    QGraphicsScene * mapScene = nullptr;
    /**
     * @brief mapView the camera, basically
     */
    QGraphicsView * mapView = nullptr;
    /**
     * @brief sections vector storing every section of the map
     */
    std::vector<MapSection *> sections;
    /**
     * @brief tileSets vector storing the tilesets used to render the map
     */
    std::vector<TileSet *> * tileSets;
    /**
     * @brief loadedTiles map storing the texture of every tile in the map, as well as its ID
     */
    std::map<int, QPixmap*> loadedTiles;
    /**
     * @brief actuallyLoadedTiles vector storing every Tile object in the map
     */
    std::vector<Tile *> * actuallyLoadedTiles = nullptr;
    /**
     * @brief itsPlayer the player that will venture the map
     */
    Player* itsPlayer;
public:
    /**
     * @brief Map the constructor of the map class
     * @param defaultSection
     * @param availableTileSets
     */
    Map(MapSection * defaultSection, std::vector<TileSet*, std::allocator<TileSet*> > * availableTileSets);
    ~Map();
    /**
     * @brief load loads the map in the scene
     */
    void load();
    /**
     * @brief getMap getter for the Map class
     * @return every section from the map
     */
    std::vector<MapSection *>* getMap();
    /**
     * @brief getScene getter for mapScene
     * @return mapScene
     */
    QGraphicsScene * getScene();
    /**
     * @brief getView getter for mapView
     * @return mapView
     */
    QGraphicsView * getView();
    /**
     * @brief getActuallyLoadedTiles getter for actuallyLoadedTiles
     * @return actuallyLoadedTiles
     */
    std::vector<Tile *> *getActuallyLoadedTiles() const;
    /**
     * @brief setItsPlayer setter for itsPlayer
     * @param playerthe Player to be set as our current map's player
     */
    void setItsPlayer(Player* player);
    /**
     * @brief getItsPlayer getter for itsPlayer
     * @return itsPlayer
     */
    Player* getItsPlayer();
public slots:
    /**
     * @brief updateView updates the view to follow the player
     */
    void updateView();
};

#endif // MAP_H
