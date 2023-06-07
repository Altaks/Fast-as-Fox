#ifndef FOX_H
#define FOX_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

#include <QGraphicsPixmapItem>
#include <QElapsedTimer>
#include <QGraphicsView>

class Fox : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

public:
    explicit Fox(QGraphicsScene *parentScene, QGraphicsView *parentView);
    void updateFrame();
    void startRunning();
    void stopRunning();
    void jump();
    void crouch();
    void reset();
    QPointF getSpritePosition() const;
    QPixmap getSpritePixmap() const;
    void stopMoving();
    void startMoving();
    void moveTo(int x, int y);

private:
    QPixmap *walkSpriteSheet;
    QPixmap *runSpriteSheet;
    QPixmap *stopSpriteSheet;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int currentFrame;
    bool isRunning;
    bool isStopped;
    QPointF spritePosition;
    QPointF spriteVelocity;
    const float groundLevel = 125.0f;
    const QPointF gravity = QPointF(0, 2); // 1 or 2 or 3 ... > increasing gravity
    void updatePixmap();
    QGraphicsView *view;

signals:
    void reachedEnd();

};


#endif // FOX_H
