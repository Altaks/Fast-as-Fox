#include "spike.h"
#include "constants.h"

Spike::Spike(QGraphicsScene *parentScene, std::pair<int, int> spawnPosition) : QGraphicsPixmapItem(nullptr)
{
    spriteSheet = new QPixmap(SPIKE);
    scene = parentScene;
    scene->addItem(this);
    attacking = false;
    this->spritePosition = {spawnPosition.first*32, scene->height() - spawnPosition.second*32};
    this->setPos(this->spritePosition.first,this->spritePosition.second);
    QRect frameRect(0, 0, TILE_SIZE, TILE_SIZE);
    this->setPixmap(spriteSheet->copy(frameRect));
    this->update();
}

const std::pair<int, int> &Spike::getSpritePosition() const
{
    return spritePosition;
}

QGraphicsScene *Spike::getScene() const
{
    return scene;
}

bool Spike::getAttacking() const
{
    return attacking;
}

void Spike::setAttacking(bool newAttacking)
{
    if(newAttacking == true && attacking == false)
        emit playerLoseHealth();

    attacking = newAttacking;
}
