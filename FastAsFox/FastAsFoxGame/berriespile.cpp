#include "berriespile.h"
#include "constants.h"
#include <QDebug>

BerriesPile::BerriesPile(QGraphicsScene * theScene, pair<int, int> endPose, int sectionHeight)
{
    BerriesPileSprite = new QPixmap(":/tasDeBaies/sprites/tasDeBaies.png");
    if (BerriesPileSprite->isNull()==true){
        qDebug("fichier introuvable");
    }
    else {
        this->tasDeBaies =new GameObject();
        scene=theScene;
        QRect placement(0,0,TILE_SIZE,TILE_SIZE);
        this->tasDeBaies->setRectangle(placement);

        double graphicsX = endPose.first * 32;
        double graphicxY = (sectionHeight - endPose.second) * 32;

        setPos(graphicsX, graphicxY);

        scene->addItem(this);
        *BerriesPileSprite=BerriesPileSprite->scaled(32,32);
        this->setPixmap(*BerriesPileSprite);
        this->update();
    }
}
