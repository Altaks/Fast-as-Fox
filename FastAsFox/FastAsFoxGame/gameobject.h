#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>
#include "collisionside.h"

/**
 * @brief The GameObject class represents a game object.
 *
 * The GameObject class is a base class for various game objects and provides
 * functionality for collision detection.
 */
class GameObject : public QObject
{
    Q_OBJECT

    QRect rectangle; /**< The rectangle representing the object's position and size. */

public:
    /**
     * @brief Constructs a GameObject object with the given parent QObject.
     * @param parent The parent QObject of the GameObject.
     */
    GameObject(QObject *parent = nullptr);
    /**
     * @brief getRectangle get the area of the game object
     * @return a rectangle that represents the area of the object
     */
    const QRect &getRectangle() const;

    /**
     * @brief Sets the rectangle representing the position and size of the object.
     * @param newRectangle The new rectangle to set.
     */
    void setRectangle(const QRect &newRectangle);
    /**
     * @brief collides returns the side of a tile the current object collided on
     * @param hitBoxTile the rectangle of the tile
     * @param hitBoxObject the rectangle our current object
     * @return the side of the tile our object has collided on
     */
static std::pair<std::optional<CollisionSide>, std::optional<CollisionSide>> collides(QRect hitBoxTile, QRect hitBoxObject);
};

#endif // GAMEOBJECT_H
