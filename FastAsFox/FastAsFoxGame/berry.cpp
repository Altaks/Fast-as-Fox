#include "berry.h"
#include "level.h"
#include "powerup.h"
#include "powerdown.h"

#include <random>

QPixmap *Berry::getTexture() const
{
    return texture;
}

void Berry::setTexture(QPixmap *newTexture)
{
    texture = newTexture;
}

QGraphicsScene *Berry::getScene() const
{
    return scene;
}

void Berry::setScene(QGraphicsScene *newScene)
{
    scene = newScene;
}

Berry::Berry(QGraphicsScene * scene)
{
    this->scene = scene;
}

Berry * Berry::generateRandom(QGraphicsScene * scene, std::pair<int, int> spawnpoint){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distribution(0, 4);

    std::uniform_int_distribution<int> random_type(0, 1);

    if((bool)random_type(eng)){ // implicit conversion to boolean
        PowerDownType type = (PowerDownType)distribution(eng);
        return new PowerDown(scene, type, spawnpoint);
    } else {
        PowerUpType type = (PowerUpType)distribution(eng);
        return new PowerUp(scene, type, spawnpoint);
    }    
}

void Berry::onCollide(Player * fox){
    qWarning() << "Called non overwritten function onCollide from Berry\n";
}

void Berry::applyEffect(Level * level, Player * fox){
    qWarning() << "Called non overwritten function applyEffect from Berry\n";
}

QPixmap * Berry::queryPixmapPowerUp(PowerUpType type){
    switch (type) {
        case SPEED_TYPE:            return new QPixmap(QString::fromStdString(SPEED));
        case DOUBLE_JUMP_TYPE:      return new QPixmap(QString::fromStdString(DOUBLE_JUMP));
        case CHRONOFREEZE_TYPE:     return new QPixmap(QString::fromStdString(CHRONO_FREEZE));
        case HEALTH_TYPE:           return new QPixmap(QString::fromStdString(HEALTH));
        case DASH_TYPE:             return new QPixmap(QString::fromStdString(DASH));
    default:
        QPixmap * map = new QPixmap(32, 32);
        map->fill(Qt::green);
        return map;
    }
};


QPixmap * Berry::queryPixmapPowerDown(PowerDownType type){
    switch (type) {
        case SLOW_TYPE:             return new QPixmap(QString::fromStdString(SLOW));
        case TOO_FAST_TYPE:         return new QPixmap(QString::fromStdString(TOO_FAST));
        case BUMP_TYPE:             return new QPixmap(QString::fromStdString(BUMP));
        case INVIS_TYPE:            return new QPixmap(QString::fromStdString(INVIS));
        case EXPLOOOSION_TYPE:      return new QPixmap(QString::fromStdString(EXPLOOOSION));
    default:
        QPixmap * map = new QPixmap(32, 32);
        map->fill(Qt::red);
        return map;
    }
}
