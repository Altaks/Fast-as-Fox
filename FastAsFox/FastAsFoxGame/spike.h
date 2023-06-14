#ifndef SPIKE_H
#define SPIKE_H


#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include <QObject>

class Spike : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    explicit Spike(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition);

    const std::pair<int, int> &getSpritePosition() const;

    QGraphicsScene *getScene() const;

    bool getAttacking() const;
    void setAttacking(bool newAttacking);

private:
    QPixmap *spriteSheet;
    QGraphicsScene *scene;
    bool attacking;
    std::pair<int,int> spritePosition;


signals:
    void playerLoseHealth();

};

#endif // SPIKE_H
