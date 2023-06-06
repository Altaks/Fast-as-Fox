#include "gameobject.h"
#include "constants.h"


const QRect &GameObject::getRectangle() const
{
    return rectangle;
}

void GameObject::setRectangle(const QRect &newRectangle)
{
    rectangle = newRectangle;
}

GameObject::GameObject(QObject *parent)
    : QObject{parent}
{

}

/**
 * @brief GameObject::collides Returns ths side on which an object has collided with the gameObject on which the function is called
 * @param object the object that has collided with our GameObject
 * @return the side of our gameObject object has collided on, or nullopt if no collision has happened
 */
std::optional<CollisionSide> GameObject::collides(GameObject *object)
{
    QRect hitBoxTile = this->rectangle;
    QRect hitBoxObject = object->rectangle;

    QRect leftRect = QRect(hitBoxTile.left() - COLLISION_OFFSET, hitBoxTile.top(), COLLISION_OFFSET, hitBoxTile.height());
    QRect rightRect = QRect(hitBoxTile.right(), hitBoxTile.top(), COLLISION_OFFSET, hitBoxTile.height());
    QRect topRect = QRect(hitBoxTile.left() - COLLISION_OFFSET, hitBoxTile.top() - COLLISION_OFFSET, hitBoxTile.width() + COLLISION_OFFSET*2, COLLISION_OFFSET);
    QRect bottomRect = QRect(hitBoxTile.left() - COLLISION_OFFSET, hitBoxTile.bottom(), hitBoxTile.width() + COLLISION_OFFSET*2, COLLISION_OFFSET);

    qreal maxIntersection = 0;
    static CollisionSide side;

    if (leftRect.intersects(hitBoxObject))
    {
        QRectF intersection = leftRect.intersected(hitBoxObject);
        if (intersection.width() > maxIntersection)
        {
            maxIntersection = intersection.width();
            side = LEFT;
        }
    }

    if (rightRect.intersects(hitBoxObject))
    {
        QRectF intersection = rightRect.intersected(hitBoxObject);
        if (intersection.width() > maxIntersection)
        {
            maxIntersection = intersection.width();
            side = RIGHT;
        }
    }

    if (topRect.intersects(hitBoxObject))
    {
        QRectF intersection = topRect.intersected(hitBoxObject);
        if (intersection.height() > maxIntersection)
        {
            maxIntersection = intersection.height();
            side = TOP;
        }
    }

    if (bottomRect.intersects(hitBoxObject))
    {
        QRectF intersection = bottomRect.intersected(hitBoxObject);
        if (intersection.height() > maxIntersection)
        {
            maxIntersection = intersection.height();
            side = BOTTOM;
        }
    }

    if (maxIntersection > 0) return side;
    else return std::nullopt;
}
