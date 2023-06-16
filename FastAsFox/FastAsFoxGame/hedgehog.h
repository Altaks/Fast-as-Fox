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

    /**
     * @brief Hedgehog constructor
     * @param parentScene a pointer to the scene where the hedgehog spawns in
     * @param spawnPosition the coordinates of spawn
     */
    explicit Hedgehog(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition);

    /**
     * @brief updateFrame updates the animation
     */
    void updateFrame();

    /**
     * @brief getSpritePosition returns the position of the animated sprite
     * @return a pair of X and Y
     */
    std::pair<int,int> getSpritePosition() const;
    QGraphicsScene *getScene() const;

    /**
     * @brief changeDirection switches the direction of the hedgehog
     */
    void changeDirection();


    void setAttacking(bool newAttacking);
    bool getAttacking() const;

    bool getStopAnimation() const;

    QTimer *getTimer() const;

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
    /**
     * @brief updatePosition a slot that is triggered to update the position of the hedgehog in the scene
     */
    void updatePosition();

signals:
    /**
     * @brief playerLoseHealth a signal emitted when the player looses health
     */
    void playerLoseHealth();

};

#endif // HEDGEHOG_H
