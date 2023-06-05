#include "player.h"

Player::Player(QObject *parent)
    : QObject(parent)
{
    inAir = false;
    onGround = true;
    velocity = QVector2D(0, 0);
}

Player::~Player() {}

bool Player::isOnAir() const
{
    return inAir;
}

bool Player::isOnGround() const
{
    return onGround;
}

void Player::setVelocity(int x, int y)
{
    velocity.setX(x);
    velocity.setY(y);
}

void Player::setVelocity(const QVector2D &vec)
{
    velocity = vec;
}

void Player::addVelocity(int x, int y)
{
    velocity += QVector2D(x, y);
}

void Player::addVelocity(const QVector2D &vec)
{
    velocity += vec;
}

void Player::updatePosition()
{
    // Update player position based on velocity
    // You can implement your logic here
}

void Player::updateAnimation()
{
    // Update player animation based on the current state
    // You can implement your logic here
}
