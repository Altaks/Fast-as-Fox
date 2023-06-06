#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>
#include "CollisionSide.h"

class GameObject : public QObject
{
    Q_OBJECT

    QRect rectangle;
public:
    GameObject(QObject *parent = nullptr);
    virtual std::optional<CollisionSide> collides(GameObject* object);
    const QRect &getRectangle() const;
    void setRectangle(const QRect &newRectangle);
};

#endif // GAMEOBJECT_H
