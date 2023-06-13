#ifndef PLAYER_H
#define PLAYER_H
#include <QVector2D>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"
#include "map.h"

class Berry;

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
     * @brief playerJump set to true if the player is jumping, false if he isn't
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
    std::pair<int, int> spawnCoords;

    bool revivalEnabled=false; // boolean if the revival berrys got eaten

    Berry * actualBerry; //the berry he got
public:
    /**
     * @brief Player Constructor for the player class
     * @param map the map the player will be venturing
     * @param parent the parent object of Player (neede for QObjects)
     */
    Player(Map * map, std::pair<int, int> spawnCoords, QObject *parent);
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
    bool isStillOnGround(std::pair<std::optional<CollisionSide>, std::optional<CollisionSide> > collisionCompute) const;


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
    void playerAccelerated();
    void playerJumped();
    void playerSlowedDown();

    void eatBerry();// function to eat a berry that the player get
    Berry* getActualBerry(); // get for the actual berry stocked in the player
    void setRevival();
    bool getRevival();
signals:
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
#endif //PLAYER_H
