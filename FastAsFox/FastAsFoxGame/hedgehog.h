#ifndef HEDGEHOG_H
#define HEDGEHOG_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

#include <QGraphicsPixmapItem>
#include <QElapsedTimer>

class Hedgehog : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    explicit Hedgehog(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition);
    void updateFrame();
    std::pair<int,int> getSpritePosition() const;
    QGraphicsScene *getScene() const;
    void changeDirection();
    void setAttacking(bool newAttacking);

    bool getAttacking() const;

    bool getStopAnimation() const;

private:
    QPixmap *walkSpriteSheet;
    QPixmap *attackSpriteSheet;
    QPixmap *walkSpriteSheetBackward;
    QPixmap *attackSpriteSheetBackward;
    QGraphicsScene *scene;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    int walkCurrentFrame;
    int attackCurrentFrame;
    int speed;
    bool attacking;
    bool attackAnimation;
    bool goingRight;
    std::pair<int,int> spritePosition;

public slots:
    void updatePosition();

signals:
    void playerLoseHealth();

};

#endif // HEDGEHOG_H
