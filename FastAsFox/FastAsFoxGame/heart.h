#ifndef HEART_H
#define HEART_H

#include "map.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include "qlabel.h"
#include "qmainwindow.h"
#include <QPair>

class Heart : public QGraphicsPixmapItem
{
    QGraphicsScene * scene;
    QPixmap * spriteSheet;
    int xPosition;

public:
    Heart(QGraphicsScene * scene, int UIposition);
    void updateHeart(bool show);
    int getXPosition() const;
};

#endif // HEART_H
