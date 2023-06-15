#include "berriespile.h"
#include "constants.h"


#include <QDebug>


BerriesPile::BerriesPile(QGraphicsScene * theScene, pair<int, int> endPos, int sectionHeight)
{

    endPose=endPos;
    BerriesPileSprite = new QPixmap(":/tasDeBaies/sprites/tasDeBaies.png");
    this->tasDeBaies =new GameObject();
    scene=theScene;
    QRect placement(0,0,TILE_SIZE,TILE_SIZE);
    this->tasDeBaies->setRectangle(placement);

    double graphicsX = endPose.first * 32;
    double graphicsY = (sectionHeight - endPose.second) * 32;

    setPos(graphicsX, graphicsY);

    scene->addItem(this);
    *BerriesPileSprite=BerriesPileSprite->scaled(32,32);
    this->setPixmap(*BerriesPileSprite);
    this->update();
}

bool BerriesPile::isAtTheEnd(Fox* fox){

    QRect pile(endPose.first, endPose.second, TILE_SIZE, TILE_SIZE);

    QRect foxRect(fox->getSpritePosition().first,fox->getSpritePosition().second,fox->pixmap().width(),fox->pixmap().height());


    return GameObject::collides(pile, foxRect) != std::pair<std::optional<CollisionSide>,std::optional<CollisionSide>>(std::nullopt, std::nullopt);
}
