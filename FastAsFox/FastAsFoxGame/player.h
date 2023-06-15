
#ifndef PLAYER_H
#define PLAYER_H
#include <QVector2D>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"
#include "map.h"

class PowerUp;

class Player : public GameObject
{
    Q_OBJECT
private:
    bool inAir;
    bool onGround;
    bool playerJump;
    bool fast;
    bool againstWall;
    bool isJumping;
    bool touchedCeiling;
    bool isFalling;
    int hp;
    double velocity = V0;
    float jumpAngle = ALPHA;
    Fox* animation;
    Map * map;
    std::chrono::time_point<std::chrono::system_clock> lastJumpTimeStamp; // Not used for powerups
    std::chrono::time_point<std::chrono::system_clock> lastDashTimeStamp; // 5 sec
    std::chrono::time_point<std::chrono::system_clock> lastSpeedTimeStamp; // 5 sec
    std::pair<int, int> spawnCoords;
    std::pair<int,int> spritePosition;
    PowerUp * stockedPowerUp = nullptr;
public:
    Player(Map * map, std::pair<int, int> spawnCoords, QObject *parent = nullptr);
    ~Player();
    bool isOnAir() const;
    bool isOnGround() const;
    bool isStillOnGround(std::pair<std::optional<CollisionSide>, std::optional<CollisionSide> > collisionCompute) const;
    Fox *getAnimation() const;
    void setInAir(bool newInAir);
    void setOnGround(bool newOnGround);
    void setLastJumpTimeStamp(std::chrono::time_point<std::chrono::system_clock> newLastJumpTimeStamp);
    void setY(double newY);
    void setX(double newX);
    void playerAccelerated();
    void playerJumped();
    void playerSlowedDown();
    const std::pair<int, int> &getSpritePosition() const;


    int getHp() const;

    void setHp(int newHp);

    PowerUp *getStockedPowerUp() const;
    void setStockedPowerUp(PowerUp *newStockedPowerUp);

    double getVelocity() const;
    void setVelocity(double newVelocity);
    float getJumpAngle() const;
    void setJumpAngle(float newJumpAngle);

    std::chrono::time_point<std::chrono::system_clock> getLastDashTimeStamp() const;
    void setLastDashTimeStamp(std::chrono::time_point<std::chrono::system_clock> newLastDashTimeStamp);
    std::chrono::time_point<std::chrono::system_clock> getLastSpeedTimeStamp() const;
    void setLastSpeedTimeStamp(std::chrono::time_point<std::chrono::system_clock> newLastSpeedTimeStamp);

signals:
    void playerMoved();
    void playerDeath();
public slots:
    void updatePosition();
    void updateHealthbar();
};
#endif //PLAYER_H
