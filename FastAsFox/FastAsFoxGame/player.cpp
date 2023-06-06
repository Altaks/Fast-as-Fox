#include "player.h"

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

void Player::updatePosition(const std::vector<Tile *> tiles)
{
    /**
    // Update player position based on velocity
    float Vx = velocity.x();
    float Vy = velocity.y();

    // Apply gravity
    Vy += gravity;

    // Apply tile collision detection and response
    QRectF playerRect = animation->boundingRect().translated(Vx, Vy);

    for (Tile *tile : tiles) {
        if (playerRect.intersects(tile->getRectangle())) {
            // Get the collision side
            std::optional<CollisionSide> collisionSide = tile->collides(this);

            if (collisionSide) {
                // Respond to the collision based on the collision side
                switch (*collisionSide) {
                case CollisionSide::TOP:
                    Vy = 0; // Stop vertical velocity
                    onGround = true;
                    inAir = false;
                    break;
                case CollisionSide::BOTTOM:
                    Vy = 0; // Stop vertical velocity
                    break;
                case CollisionSide::LEFT:
                    Vx = 0; // Stop horizontal velocity
                    break;
                case CollisionSide::RIGHT:
                    Vx = 0; // Stop horizontal velocity
                    break;
                }
            }
        }
    }

    // Update player's position using the updated velocity
    QPointF newPosition = animation->pos() + QPointF(Vx, Vy);
    animation->setPos(newPosition);
**/
}

void Player::updateAnimation()
{
    // Update player animation based on the current state
}
