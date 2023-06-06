#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "gameobject.h"
#include "tileset.h"
#include "mapsection.h"

/**
 * @brief The Map class represents a game map.
 *
 * The Map class is responsible for managing and displaying the game map.
 */
class Map
{
private:
    QGraphicsScene *mapScene = nullptr; /**< The graphics scene for the map. */
    QGraphicsView *mapView = nullptr;   /**< The graphics view for the map. */
    std::vector<MapSection *> sections; /**< The sections of the map. */
    std::vector<TileSet *> *tileSets;   /**< The available tile sets for the map. */
    std::map<int, QPixmap *> loadedTiles; /**< The loaded tiles for the map. */

public:
    /**
     * @brief Constructs a Map object with the specified default section and available tile sets.
     * @param defaultSection The default section of the map.
     * @param availableTileSets The available tile sets for the map.
     */
    Map(MapSection *defaultSection, std::vector<TileSet *, std::allocator<TileSet *>> *availableTileSets);

    /**
     * @brief Destructor to clean up dynamically allocated resources.
     */
    ~Map();

    /**
     * @brief Loads the map by placing tiles in the scene.
     */
    void load();

    /**
     * @brief Returns a pointer to the vector of map sections.
     * @return A pointer to the vector of map sections.
     */
    std::vector<MapSection *> *getMap();

    /**
     * @brief Returns the graphics scene of the map.
     * @return The graphics scene of the map.
     */
    QGraphicsScene *getScene();

    /**
     * @brief Returns the graphics view of the map.
     * @return The graphics view of the map.
     */
    QGraphicsView *getView();

private slots:
    /**
     * @brief Updates the view to center on the specified game object.
     * @param obj The game object to center the view on.
     */
    void updateView(GameObject *obj);
};

#endif // MAP_H
