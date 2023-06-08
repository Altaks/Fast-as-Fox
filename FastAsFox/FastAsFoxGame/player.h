#ifndef PLAYER_H
#define PLAYER_H
#include <QVector2D>
#include "animatedsprite.h"
#include "constants.h"
#include "tile.h"
#include "map.h"

class Player : public QObject
{
    Q_OBJECT

private:
    bool inAir;
    bool onGround;
    QVector2D velocity;
    Fox* animation;
    Map * map;

public:
    Player(Map * map, QObject *parent = nullptr);
    ~Player();

    bool isOnAir() const;
    bool isOnGround() const;

    void setVelocity(int x, int y);
    void setVelocity(const QVector2D &vec);
    void addVelocity(int x, int y);
    void addVelocity(const QVector2D &vec);

    Fox *getAnimation() const;

signals:
    void jump();
    void accelerate();
    void slowdown();
    void playerMoved();

public slots:
    void updatePosition();
    void updateAnimation();
};

#endif // PLAYER_H
