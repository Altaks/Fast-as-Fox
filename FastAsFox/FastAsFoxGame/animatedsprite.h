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
    /**
     * @brief Fox the constructor for the Fox class
     * @param parentScene
     */
    explicit Fox(QGraphicsScene *parentScene);
    /**
     * @brief updateFrame updates the frame of the fox's animation
     */
    void updateFrame();
    /**
     * @brief startRunning set the fox's animation to the running one
     */
    void startRunning();
    /**
     * @brief stopRunning set the fox's animation to the walking one
     */
    void stopRunning();
    /**
     * @brief jump set the fox's animation to the jumping one
     */
    void jump();
    /**
     * @brief crouch set the fox's animation to the crounching one
     */
    void crouch();
    /**
     * @brief reset
     */
    void reset();// undefined
    /**
     * @brief getSpritePosition getter for the fox's sprite's position
     * @return the sprite's position
     */
    std::pair<int,int> getSpritePosition() const;
    /**
     * @brief getIsRunning getter for isRunning
     * @return isRunning (true if the fox's current animation is the running one, false if it isn't)
     */
    bool getIsRunning() const;
    /**
     * @brief setIsRunning setter for isRunning
     * @param newIsRunning a boolean indicating if the fox should switch to its running animation
     */
    void setIsRunning(bool newIsRunning);
    /**
     * @brief getScene getter for scene
     * @return scene
     */
    QGraphicsScene *getScene() const;

private:
    /**
     * @brief walkSpriteSheet the path to the spritesheet of the fox's walking animation
     */
    QPixmap *walkSpriteSheet;
    /**
     * @brief runSpriteSheet the path to the spritesheet of the fox's running animation
     */
    QPixmap *runSpriteSheet;
    /**
     * @brief scene
     */
    QGraphicsScene *scene;
    /**
     * @brief timer timer used to time the updates of fox's sprite
     */
    QTimer *timer;
    /**
     * @brief elapsedTimer the timer's elapsed time
     */
    QElapsedTimer *elapsedTimer;
    int currentFrame;
    /**
     * @brief isRunning Bolean set to true if the fox is running, and to false if he isn't
     */
    bool isRunning;
    /**
     * @brief spritePosition x,y position of the sprite
     */
    std::pair<int,int> spritePosition;
    /**
     * @brief spriteVelocity x,y velocity of the sprite
     */
    std::pair<int,int> spriteVelocity;
    /**
     * @brief updatePixmap updates the fox's sprite
     */
    void updatePixmap();

signals:
    /**
     * @brief endOfMapReached signals that the end of the map has been reached by the player
     */
    void endOfMapReached();

};


#endif // ANIMATEDSPRITE_H
