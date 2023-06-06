#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "QtGui/qpixmap.h"
#include <QElapsedTimer>
#include "gameobject.h"
#include <QGraphicsPixmapItem>

#include <QGraphicsPixmapItem>
#include <QElapsedTimer>

/**
 * @brief The Fox class represents a fox character in a game.
 *
 * The Fox class inherits from QObject and QGraphicsPixmapItem and provides functionality
 * for animating and controlling the fox's movements.
 */
class Fox : public QObject, public QGraphicsPixmapItem {

public:
    /**
     * @brief Constructs a Fox object with the given parent QGraphicsScene.
     * @param parentScene The parent QGraphicsScene in which the Fox will be placed.
     */
    explicit Fox(QGraphicsScene *parentScene);

    /**
     * @brief Updates the current frame of the fox animation.
     */
    void updateFrame();

    /**
     * @brief Starts the running animation of the fox.
     */
    void startRunning();

    /**
     * @brief Stops the running animation of the fox.
     */
    void stopRunning();

    /**
     * @brief Makes the fox jump.
     */
    void jump();

    /**
     * @brief Makes the fox crouch.
     */
    void crouch();

    /**
     * @brief Resets the fox's position and state to default.
     */
    void reset();

    /**
     * @brief Returns the position of the fox sprite.
     * @return The position of the fox sprite as a QPointF.
     */
    QPointF getSpritePosition() const;

    /**
     * @brief Returns the pixmap of the current fox sprite.
     * @return The pixmap of the current fox sprite as a QPixmap.
     */
    QPixmap getSpritePixmap() const;

private:
    QPixmap *walkSpriteSheet; /**< The walk animation sprite sheet for the fox. */
    QPixmap *runSpriteSheet; /**< The run animation sprite sheet for the fox. */
    QGraphicsScene *scene; /**< The parent QGraphicsScene of the fox. */
    QTimer *timer; /**< The timer used for updating the fox animation. */
    QElapsedTimer *elapsedTimer; /**< The elapsed timer used for frame rate control. */
    int currentFrame; /**< The index of the current frame in the sprite sheet. */
    bool isRunning; /**< A flag indicating whether the fox is currently running. */
    QPointF spritePosition; /**< The position of the fox sprite. */
    QPointF spriteVelocity; /**< The velocity of the fox sprite. */
    const float groundLevel = 125.0f; /**< The y-coordinate of the ground level. */
    const QPointF gravity = QPointF(0, 2); /**< The gravity applied to the fox. */

    /**
     * @brief Updates the pixmap of the fox sprite based on the current frame.
     */
    void updatePixmap();

signals:
    /**
     * @brief Signal emitted when the fox reaches the end of the map.
     */
    void endOfMapReached();

};

#endif // ANIMATEDSPRITE_H
