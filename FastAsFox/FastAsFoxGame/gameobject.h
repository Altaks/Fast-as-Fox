#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>
#include "collisionside.h"


class GameObject : public QObject
{
    Q_OBJECT

    QRect rectangle;
public:
    /**
     * @brief GameObject constructor for the gameobject class
     * @param parent the parent of the object (required for QObjects)
     */
    GameObject(QObject *parent = nullptr);
    /**
     * @brief getRectangle get the area of the game object
     * @return a rectangle that represents the area of the object
     */
    const QRect &getRectangle() const;
    /**
     * @brief setRectangle Creates a rectangle of the same position and area as the object
     * @param newRectangle the rectangle that will be attributed to the object as its rectangle
     */
    void setRectangle(const QRect &newRectangle);
    /**
     * @brief collides returns the side of a tile the current object collided on
     * @param hitBoxTile the rectangle of the tile
     * @param hitBoxObject the rectangle our current object
     * @return the side of the tile our object has collided on
     */
    static std::optional<CollisionSide> collides(QRect hitBoxTile, QRect hitBoxObject);
};

#endif // GAMEOBJECT_H
