#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>
#include <qrect.h>

class GameObject : public QObject
{
    Q_OBJECT

    QRect rectangle;
public:
    GameObject(QObject *parent = nullptr);
    virtual bool collides(QObject* object)=0;
    const QRect &getRectangle() const;
    void setRectangle(const QRect &newRectangle);
};

#endif // GAMEOBJECT_H
