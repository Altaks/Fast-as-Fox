﻿#ifndef PLAYER_H
#define PLAYER_H
#include <QVector2D>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"
#include "map.h"

class Player : public GameObject
{
    Q_OBJECT

private:
    /**
     * @brief inAir set to true if the layer is in air, false if it isn't
     */
    bool inAir;
    /**
     * @brief onGround set to true if the layer is on the ground, false if it isn't
     */
    bool onGround;
    /**
     * @brief playerJump set to true if the player is jumping, false if he isnt
     */
    bool playerJump;
    /**
     * @brief fast set to true if the player is running, false if he is walking
     */
    bool fast;
    /**
     * @brief velocity stores the velocity of the player
     */
    QVector2D velocity;
    /**
     * @brief animation The current animation of the player
     */
    Fox* animation;
    /**
     * @brief map The map the player is venturing
     */
    Map * map;
    /**
     * @brief lastJumpTimeStamp stores the time the player jumped for the last time
     */
    std::chrono::time_point<std::chrono::system_clock> lastJumpTimeStamp;

public:
    /**
     * @brief Player Constructor for the player class
     * @param map the map the player will be venturing
     * @param parent the parent object of Player (neede for QObjects)
     */
    Player(Map * map, QObject *parent = nullptr);
    ~Player();

    /**
     * @brief isOnAir getter for inAir
     * @return inAir
     */
    bool isOnAir() const;
    /**
     * @brief isOnGround getter for onGround
     * @return onGround
     */
    bool isOnGround() const;
    /**
     * @brief isStillOnGround checks if the player is still on the ground
     * @param collisionCompute the side on which the player is colliding with tiles, or nullopt if the player isn't colliding with anything
     * @return fales if the player isn't on th ground, true if he still is
     */
    bool isStillOnGround(std::optional<CollisionSide> collision) const;

    /**
     * @brief setVelocity setter for the player's velocity
     * @param x the x velocity to be given to the player
     * @param y the y velocity to be given to the player
     */
    void setVelocity(int x, int y);
    void setVelocity(const QVector2D &vec);

    /**
     * @brief addVelocity adds velocity to the player
     * @param x the value to add to the player's pre-existing x velocity
     * @param y the value to add to the player's pre-existing y velocity
     */
    void addVelocity(int x, int y);
    void addVelocity(const QVector2D &vec);

    /**
     * @brief getAnimation getter for the player's animations
     * @return animations
     */
    Fox *getAnimation() const;
    /**
     * @brief setInAir setter for inAir
     * @param newInAir a boolean indicating if the player is in air
     */
    void setInAir(bool newInAir);
    /**
     * @brief setOnGround setter for onGround
     * @param newOnGround a boolean indicating if the player is on the ground
     */
    void setOnGround(bool newOnGround);
    /**
     * @brief setLastJumpTimeStamp setter for lastTimeJumpStamp
     * @param newLastJumpTimeStamp the last time the player jumped
     */
    void setLastJumpTimeStamp(std::chrono::time_point<std::chrono::system_clock> newLastJumpTimeStamp);

    void setY(double newY);

    void setX(double newX);

signals:
    void jump();
    void accelerate();
    void slowdown();
    void playerMoved();

public slots:
    /**
     * @brief updatePosition updates the player's potision
     */
    void updatePosition();
    /**
     * @brief updateAnimation update the player's animation
     */
    void updateAnimation();
};

#endif // PLAYER_H
