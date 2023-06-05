#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT

public:
    GameObject(QObject *parent = nullptr);
    virtual bool collides(QObject* object)=0;
};

#endif // GAMEOBJECT_H
