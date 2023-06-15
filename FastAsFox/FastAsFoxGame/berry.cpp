#include "berry.h"
#include "level.h"

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

Berry * Berry::generateRandom(){
    return nullptr;
}

void Berry::onCollide(Player * fox){
    qWarning() << "Called non overwritten function onCollide from Berry\n";
}

void Berry::applyEffect(Level * level, Player * fox){
    qWarning() << "Called non overwritten function applyEffect from Berry\n";
}

QPixmap * Berry::queryPixmap(PowerUpType type){
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
