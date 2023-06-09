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
    void crouch();
    void reset();
    std::pair<int,int> getSpritePosition() const;

    bool getIsRunning() const;
    void setIsRunning(bool newIsRunning);

    QGraphicsScene *getScene() const;

private:
    QPixmap *walkSpriteSheet;
    QPixmap *runSpriteSheet;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int currentFrame;
    bool isRunning;
    std::pair<int,int> spritePosition;
    std::pair<int,int> spriteVelocity;
    void updatePixmap();

signals:
    void endOfMapReached();

};


#endif // ANIMATEDSPRITE_H
