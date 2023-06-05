#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "QtCore/qpoint.h"
#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT

    QObject* parent;
    QPointF location;
public:
    explicit GameObject(QObject *parent = nullptr);    
    bool collides(QObject* object);
    QObject* getParent();
};

#endif // GAMEOBJECT_H
