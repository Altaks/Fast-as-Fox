#include "player.h"
#include "tile.h"

Player::Player(QObject *parent)
    : QObject(parent)
{
    inAir = false;
    onGround = true;
    velocity = QVector2D(0, 0);
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

void Player::updatePosition(std::vector<Tile *> tiles)
{
    // Update player position based on velocity
    // You can implement your logic here

    int playerPosX = this->animation->getRectangle().x();
    int playerPosY = this->animation->getRectangle().y();

    int belowPlayerPosY = playerPosY - 1;
    bool tileBelowPlayerIsAir = false;
    for(Tile * tile : tiles){
        if((int)tile->getTileItem()->x()/32 == playerPosX && (int)tile->getTileItem()->y()/32 == belowPlayerPosY){
            if(tile->getTileid() == 0){

                // tile is air
                tileBelowPlayerIsAir = true;
                break;
            }
        }
    }

    if(isOnAir() || tileBelowPlayerIsAir){
        // set jump timestamp
    } else {

    }
}

void Player::updateAnimation()
{
    // Update player animation based on the current state
}
