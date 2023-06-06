#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>
#include "collisionside.h"


class GameObject : public QObject
{
    Q_OBJECT

protected:
    QRect rectangle;
public:
    GameObject(QObject *parent = nullptr);
    virtual std::optional<CollisionSide> collides(GameObject* object);
    virtual const QRect &getRectangle() const;
    virtual void setRectangle(const QRect &newRectangle);
};

#endif // GAMEOBJECT_H
