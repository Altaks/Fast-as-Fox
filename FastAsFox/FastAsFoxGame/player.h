
#ifndef PLAYER_H
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
    bool inAir;
    bool onGround;
    bool playerJump;
    bool fast;
    QVector2D velocity;
    Fox* animation;
    Map * map;
    std::chrono::time_point<std::chrono::system_clock> lastJumpTimeStamp;
    std::pair<int, int> spawnCoords;
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
signals:
    void playerMoved();
public slots:
    void updatePosition();
};
#endif //PLAYER_H
