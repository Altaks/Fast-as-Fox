#include "gameobject.h"
#include "QtGui/qpainter.h"
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
    QRect rightRect =   QRect(hitBoxTile.right() - COLLISION_OFFSET, hitBoxTile.top() - COLLISION_OFFSET, COLLISION_OFFSET, hitBoxTile.height() - COLLISION_OFFSET * 2);
    QRect leftRect =  QRect(hitBoxTile.left(), hitBoxTile.top() - COLLISION_OFFSET, COLLISION_OFFSET, hitBoxTile.height() - COLLISION_OFFSET * 2);
    QRect topRect =    QRect(hitBoxTile.left() + COLLISION_OFFSET, hitBoxTile.top(), hitBoxTile.width() - COLLISION_OFFSET * 2, COLLISION_OFFSET);
    QRect bottomRect = QRect(hitBoxTile.left() + COLLISION_OFFSET, hitBoxTile.bottom() - COLLISION_OFFSET, hitBoxTile.width() - COLLISION_OFFSET * 2, COLLISION_OFFSET);

    qreal maxIntersection = 0;
    std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> side = std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>>(std::nullopt, std::nullopt);


    /*QPainter painter(window);
    painter.setPen(Qt::red);
    QRect rect = rightRect;
    painter.drawRect(rect);

    painter.setPen(Qt::yellow);
    rect = leftRect;
    painter.drawRect(rect);

    painter.setPen(Qt::blue);
    rect = topRect;
    painter.drawRect(rect);

    painter.setPen(Qt::green);
    rect = bottomRect;
    painter.drawRect(rect);*/

    if (leftRect.intersects(hitBoxObject))
    {
            side.second = LEFT;
    }
    else if (rightRect.intersects(hitBoxObject))
    {
            side.second = RIGHT;
    }


    if (topRect.intersects(hitBoxObject))
    {
            side.first = TOP;
    }
    else if (bottomRect.intersects(hitBoxObject))
    {
            side.first = BOTTOM;
    }

    return side;
}
