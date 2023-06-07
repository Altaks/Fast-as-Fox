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
     * @brief Checks for collision between this object and another GameObject.
     * @param object The other GameObject to check collision with.
     * @return An optional CollisionSide indicating the side of collision, or std::nullopt if no collision occurs.
     */
    virtual std::optional<CollisionSide> collides(GameObject *object);

    /**
     * @brief Returns the rectangle representing the position and size of the object.
     * @return The rectangle representing the object.
     */
    const QRect &getRectangle() const;

    /**
     * @brief Sets the rectangle representing the position and size of the object.
     * @param newRectangle The new rectangle to set.
     */
    void setRectangle(const QRect &newRectangle);
};

#endif // GAMEOBJECT_H
