#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

#include <QGraphicsPixmapItem>
#include <QElapsedTimer>

class Fox : public QObject, public QGraphicsPixmapItem {

public:
    explicit Fox(QGraphicsScene *parentScene);
    void updateFrame();
    void startRunning();
    void stopRunning();
    void jump();
    void reset();
    QPointF getSpritePosition() const;
    QPixmap getSpritePixmap() const;
    void addScore();

private:
    QPixmap *walkSpriteSheet;
    QPixmap *runSpriteSheet;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int currentFrame;
    bool isRunning;
    QPointF spritePosition;
    QPointF spriteVelocity;
    const float groundLevel = 125.0f;
    const QPointF gravity = QPointF(0, 2); // 1 or 2 or 3 ... > increasing gravity
    void updatePixmap();
    int score;

signals:
    void endOfMapReached();

};


#endif // ANIMATEDSPRITE_H
