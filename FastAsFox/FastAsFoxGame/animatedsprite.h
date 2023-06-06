#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

class AnimatedSprite : public GameObject, public QGraphicsPixmapItem
{
    QPixmap* spriteSheet;
    QPointF spritePostion;
    int currentFrame;
    bool isRunning;
    QPixmap walkSpriteSheet;
    QPixmap runSpriteSheet;
    QElapsedTimer* elapsedTimer;
    QPointF spritePosition;

public:
    AnimatedSprite(QObject *parent = nullptr);
    void updatePosition();
    void updateAnimation();
    void setIsRunning(bool newIsRunning);
};

#endif // ANIMATEDSPRITE_H
