#include "gameobject.h"

QObject *GameObject::getParent() const
{
    return parent;
}

GameObject::GameObject(QObject *parent)
    : QObject{parent}
{

}
