#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "gameobject.h"

class AnimatedSprite : public GameObject
{
public:
    explicit AnimatedSprite(QObject *parent = nullptr);
};

#endif // ANIMATEDSPRITE_H
