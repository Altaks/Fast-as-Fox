#include "player.h"

Fox *Player::getAnimation() const
{
    return animation;
}

Player::Player(Map * map, QObject *parent)
{
    this->inAir = false;
    this->onGround = true;
    this->velocity = QVector2D(0, 0);
    this->animation = new Fox(map->getScene());
    this->animation->setZValue(1);
    this->map = map;
}

Player::~Player()
{
    delete animation;
}

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
    this->velocity.setX(x);
    this->velocity.setY(y);
}

void Player::setVelocity(const QVector2D &vec)
{
    this->velocity = vec;
}

void Player::addVelocity(int x, int y)
{
    this->velocity += QVector2D(x, y);
}

void Player::addVelocity(const QVector2D &vec)
{
    this->velocity += vec;
}

void Player::updatePosition()
{
    std::vector<Tile *>* tiles = map->getActuallyLoadedTiles();

    // Get the "game real" coordinates
    double xPlayer = ((double)this->animation->x() / 32);
    double yPlayer = ((double)this->animation->y() / 32);

    xPlayer += 0.1;

    this->animation->setPos(xPlayer * 32, yPlayer * 32);

}

void Player::updateAnimation()
{

}
