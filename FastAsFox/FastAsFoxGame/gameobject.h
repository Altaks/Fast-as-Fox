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
    GameObject(QObject *parent = nullptr);
    const QRect &getRectangle() const;
    void setRectangle(const QRect &newRectangle);
    static std::optional<CollisionSide> collides(QRect hitBoxTile, QRect hitBoxObject);
};

#endif // GAMEOBJECT_H
