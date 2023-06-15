#include "heart.h"
#include "constants.h"


int Heart::getXPosition() const
{
    return xPosition;
}

Heart::Heart(QGraphicsScene *parent, int UIposition)
{
    spriteSheet = new QPixmap(HEART);
    if(spriteSheet->isNull()) {
        qWarning() << "Failed to load spritesheet.";
    }
    scene = parent;
    this->xPosition = UIposition;
    QRect frameRect(0, 0, TILE_SIZE, TILE_SIZE);
    this->setPixmap(spriteSheet->copy(frameRect));
    this->setPos(xPosition*32,TILE_SIZE);
    scene->addItem(this);
    this->update();
}

void Heart::updateHeart(bool show)
{
    if(show)
    {
        QRect frameRect(0, 0, TILE_SIZE, TILE_SIZE);
        this->setPixmap(spriteSheet->copy(frameRect));
        this->update();
    }
    else
    {
        QRect frameRect(0, 0, 1, 1);
        this->setPixmap(spriteSheet->copy(frameRect));
        this->update();
    }
}
