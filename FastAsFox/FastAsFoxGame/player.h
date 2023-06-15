#ifndef PLAYER_H
#define PLAYER_H
#include <QVector2D>
#include <chrono>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"
#include "map.h"

using namespace std;

class Berry;

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
    int hp;
    QVector2D velocity;
    Fox* animation= nullptr;
    Map * map= nullptr;
    std::chrono::time_point<std::chrono::system_clock> lastJumpTimeStamp;
    std::pair<int, int> spawnCoords;
    std::pair<int,int> spritePosition;

    Berry * actualBerry= nullptr;
    std::chrono::time_point<std::chrono::system_clock> start, end;


public:
    Player(Map * map, std::pair<int, int> spawnCoords, QObject *parent = nullptr);
    ~Player();
    bool isOnAir() const;
    bool isOnGround() const;
    bool isStillOnGround(std::pair<std::optional<CollisionSide>, std::optional<CollisionSide> > collisionCompute) const;
    void setVelocity(int x, int y);
    void setVelocity(const QVector2D &vec);
    void addVelocity(int x, int y);
    void addVelocity(const QVector2D &vec);
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


    bool eatBerry();// function to eat a berry that the player get
    void setActualBerry(Berry * berries);
    Berry * getActualBerry();

    void addHP();
    int getHP();

signals:
    void playerMoved();
    void playerDeath();
public slots:
    void updatePosition();
    void updateHealthbar();
};
#endif //PLAYER_H
