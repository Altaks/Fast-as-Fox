#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include "qgraphicseffect.h"
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
    void updatePixmap();

    QColor originalColor;  // Store the original color
    QGraphicsColorizeEffect* colorizeEffect;  // Store the colorize effect

    void setColor(QColor color) ;

    void resetColor() ;


private:
    QPixmap *walkSpriteSheet;
    QPixmap *runSpriteSheet;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int currentFrameWalk;
    int currentFrameRun;
    bool isRunning;
    std::pair<int,int> spritePosition;
    std::pair<int,int> spriteVelocity;

signals:
    void endOfMapReached();

};


#endif // ANIMATEDSPRITE_H
