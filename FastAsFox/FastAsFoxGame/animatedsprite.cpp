#include "animatedsprite.h"


AnimatedSprite::AnimatedSprite(QObject *parent)
    : GameObject{parent}
{
    this->currentFrame=0;
    this->elapsedTimer = new QElapsedTimer();
    this->isRunning=false;
    this->spritePostion.setX(0);
    this->spritePostion.setY(0);
    this->spriteSheet = new QPixmap("../sprgsp/fke.png");
}

void AnimatedSprite::updatePosition()
{
    if(isRunning)
        this->spritePostion.setX(this->spritePostion.x()+2);
    else
        this->spritePostion.setX(this->spritePostion.x()+1);
}

void AnimatedSprite::updateAnimation()
{
    if(this->currentFrame+1==7)
        this->currentFrame=0;
}

void AnimatedSprite::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}

bool AnimatedSprite::collides(GameObject *object)
{
    return false;
}
