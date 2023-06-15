#include "powerup.h"

PowerUp::PowerUp(QGraphicsScene * scene, PowerUpType type, std::pair<int, int> spawnpoint) : Berry(scene) {
    this->type = type;

    // Apply the texture
    this->texture = Berry::queryPixmapPowerUp(type);
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

void PowerUp::onCollide(Player * player){
    if(!this->hasBeenUsed && player->getStockedPowerUp() == nullptr){ // player has no power up in its inv
        player->setStockedPowerUp(this);
        this->scene->removeItem(this);
        this->hasBeenUsed = true;
    }
}

void PowerUp::applyEffect(Level * level, Player * player){
    switch (this->type) {
        case SPEED_TYPE: {
            player->setLastSpeedTimeStamp(std::chrono::system_clock::now());
            qWarning() << "Consumed speed type power up" << "\n";
            break;
        }
        case DASH_TYPE: {
            player->setLastDashTimeStamp(std::chrono::system_clock::now());
            qWarning() << "Consumed dash type power up" << "\n";
            break;
        }
        case CHRONOFREEZE_TYPE: {
            // if counter values is at 100 -> 1 sec
            if(level->getCount() - 5 > 0) level->setCount(level->getCount() - 5); else level->setCount(0);
            qWarning() << "Consumed speed type chrono freeze up" << "\n";
            break;
        }
        case HEALTH_TYPE: {
            if(player->getHp() < 3) {
                player->setHp(player->getHp() + 1);
                emit level->updateHeartsDisplay();
            }
            qWarning() << "Consumed speed type health boost up" << "\n";
            break;
        }
        case DOUBLE_JUMP_TYPE: {
            player->setLastJumpTimeStamp(std::chrono::system_clock::now()); // resets the player jump t0
            qWarning() << "Consumed speed type double jump up" << "\n";
            break;
        }
    default:
        return;
    }
    player->setStockedPowerUp(nullptr);
    qWarning() << "Player consumed the powerup and dont have it anymore" << "\n";
}
