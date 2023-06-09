#ifndef BERRIESPILE_H
#define BERRIESPILE_H

#include "gameobject.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

using namespace std;

class BerriesPile : public GameObject, public QGraphicsPixmapItem
{
private:
    GameObject* tasDeBaies;
    QPixmap * BerriesPileSprite;
    QGraphicsScene * scene;
    pair<int,int> endPose;
public:
    BerriesPile(QGraphicsScene * theScene, pair<int,int> endPose, int sectionHeight);
};

#endif // BERRIESPILE_H
