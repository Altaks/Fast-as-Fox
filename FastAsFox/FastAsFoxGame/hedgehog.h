#ifndef HEDGEHOG_H
#define HEDGEHOG_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

#include <QGraphicsPixmapItem>
#include <QElapsedTimer>

class Hedgehog : public QObject, public QGraphicsPixmapItem {

public:
    explicit Hedgehog(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition);
    void updateFrame();
    std::pair<int,int> getSpritePosition() const;
    void updatePosition();
    QGraphicsScene *getScene() const;

private:
    QPixmap *walkSpriteSheet;
    QPixmap *attackSpriteSheet;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int walkCurrentFrame;
    int attackCurrentFrame;
    bool attacking;
    std::pair<int,int> spritePosition;

private slots:



};

#endif // HEDGEHOG_H
