#include "powerdown.h"

PowerDown::PowerDown(QGraphicsScene * scene, PowerDownType type, std::pair<int, int> spawnpoint) : Berry(scene) {
    this->type = type;

    // Apply the texture
    this->texture = Berry::queryPixmapPowerDown(type);
    QPixmap map = this->texture->scaled(32, 32);
    this->texture = new QPixmap(map);
    this->setPixmap(*this->texture);

    // Apply the coordinates to the berry
    double graphicsX = spawnpoint.first * TILE_SIZE;
    double graphicsY = scene->height() - (spawnpoint.second * TILE_SIZE);

    this->setPos(graphicsX, graphicsY);

    // Apply Z value & Add item to the scene
    this->setZValue(0);
    this->scene->addItem(this);
}

void PowerDown::onCollide(Player * player){
    if(!hasBeenPickedUp){
        this->scene->removeItem(this);
        this->applyEffect(nullptr, player);
        hasBeenPickedUp = true;
    }
}

void PowerDown::applyEffect(Level * level, Player * player){
    qInfo() << "Power down effect apply called";
    switch (this->type) {
        case SLOW_TYPE:
            player->setLastSlowTimeStamp(std::chrono::system_clock::now());
            break;
        case TOO_FAST_TYPE:
            player->setLastTooFastTimeStamp(std::chrono::system_clock::now());
            break;
        case EXPLOOOSION_TYPE:
            emit player->playerDeath();
            break;
        default:
            return;
    }
}

void PowerDown::addToScene()
{
    this->scene->addItem(this);
    this->hasBeenUsed = false;
}
