#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>
#include "collisionside.h"


class GameObject : public QObject
{
    Q_OBJECT

    /**
     * @brief rectangle the bounding rectangle that represents this object
     */
    QRect rectangle;
public:
    GameObject(QObject *parent = nullptr);
    const QRect &getRectangle() const;
    void setRectangle(const QRect &newRectangle);

    /**
     * @brief collides returns the collision sides if there's a collision between theses rectangles
     * @param hitBoxTile the first rectangle to test
     * @param hitBoxObject the second rectangle to test
     * @return a optional collision pair
     */
    static std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> collides(QRect hitBoxTile, QRect hitBoxObject);
};

#endif // GAMEOBJECT_H
