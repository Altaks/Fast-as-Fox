#ifndef SPIKE_H
#define SPIKE_H


#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include <QObject>

class Spike : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    /**
     * @brief Spike a constructor
     * @param parentScene a pointer towards the scene where the spike will spawn in
     * @param spawnPosition the coordinates where the spike spawns
     */
    explicit Spike(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition);

    const std::pair<int, int> &getSpritePosition() const;

    QGraphicsScene *getScene() const;

    bool getAttacking() const;
    void setAttacking(bool newAttacking);

private:

    /**
     * @brief spriteSheet the texture of the spike
     */
    QPixmap *spriteSheet;

    /**
     * @brief scene the currently displayed scene
     */
    QGraphicsScene *scene;

    bool attacking;
    std::pair<int,int> spritePosition;

signals:
    /**
     * @brief playerLoseHealth triggers player health diminution
     */
    void playerLoseHealth();

};

#endif // SPIKE_H
