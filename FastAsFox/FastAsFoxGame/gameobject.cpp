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

std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> GameObject::collides(QRect hitBoxTile, QRect hitBoxObject)
{
    QRect leftRect =   QRect(hitBoxTile.left(), hitBoxTile.top(), COLLISION_OFFSET, hitBoxTile.height());
    QRect rightRect =  QRect(hitBoxTile.right() - COLLISION_OFFSET, hitBoxTile.top(), COLLISION_OFFSET, hitBoxTile.height());
    QRect topRect =    QRect(hitBoxTile.left(), hitBoxTile.top() - COLLISION_OFFSET, hitBoxTile.width(), COLLISION_OFFSET);
    QRect bottomRect = QRect(hitBoxTile.left(), hitBoxTile.bottom() - COLLISION_OFFSET, hitBoxTile.width(), COLLISION_OFFSET);

    qreal maxIntersection = 0;
    std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> side = std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>>(std::nullopt, std::nullopt);


    if (rightRect.intersects(hitBoxObject))
    {
        QRectF intersection = rightRect.intersected(hitBoxObject);
        if (intersection.width() > maxIntersection)
        {
            maxIntersection = intersection.width();
            side.second = RIGHT;
        }
    }

    else if (leftRect.intersects(hitBoxObject))
    {
        QRectF intersection = leftRect.intersected(hitBoxObject);
        if (intersection.width() > maxIntersection)
        {
            maxIntersection = intersection.width();
            side.second = LEFT;
        }
    }


    if (topRect.intersects(hitBoxObject))
    {
        QRectF intersection = topRect.intersected(hitBoxObject);
        if (intersection.height() > maxIntersection)
        {
            maxIntersection = intersection.height();
            side.first = TOP;
        }
    }

    else if (bottomRect.intersects(hitBoxObject))
    {
        QRectF intersection = bottomRect.intersected(hitBoxObject);
        if (intersection.height() > maxIntersection)
        {
            maxIntersection = intersection.height();
            side.first = BOTTOM;
        }
    }

    return side;
}
