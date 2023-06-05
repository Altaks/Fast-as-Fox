#include "gameobject.h"

const QRect &GameObject::getRectangle() const
{
    return rectangle;
}

void GameObject::setRectangle(const QRect &newRectangle)
{
    rectangle = newRectangle;
}

GameObject::GameObject(QObject *parent)
    : QObject{parent}
{

}
