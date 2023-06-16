#ifndef BERRIESPILE_H
#define BERRIESPILE_H

#include "gameobject.h"
#include "animatedsprite.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

using namespace std;

class BerriesPile : public GameObject, public QGraphicsPixmapItem
{
private:
    /**
     * @brief tasDeBaies the game object that correspond to the berries pile
     */
    GameObject* tasDeBaies;

    /**
     * @brief BerriesPileSprite the texture of the berries pile
     */
    QPixmap * BerriesPileSprite;

    /**
     * @brief scene the scene that the berries pile is in
     */
    QGraphicsScene * scene;

    /**
     * @brief endPose the spawning coordinates of the berries pile
     */
    pair<int,int> endPose;
public:
    /**
     * @brief BerriesPile constructor
     * @param theScene the scene where the berries pile spawns in
     * @param endPose the coordinates where the berries pile spawns
     * @param sectionHeight the height of the map section
     */
    BerriesPile(QGraphicsScene * theScene, pair<int,int> endPose, int sectionHeight);
public slots:

    /**
     * @brief isAtTheEnd returns whether or not the player collides with the berries pile
     * @param fox the fox animation
     * @return a boolean
     */
    bool isAtTheEnd(Fox* fox);
};

#endif // BERRIESPILE_H
