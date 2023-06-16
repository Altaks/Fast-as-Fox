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
    /**
     * @brief scene the scene where the heart shows in
     */
    QGraphicsScene * scene;

    /**
     * @brief spriteSheet the texture of the heart
     */
    QPixmap * spriteSheet;

    /**
     * @brief xPosition the position in X coordinates on the screen
     */
    int xPosition;

public:

    /**
     * @brief Heart a constructor
     * @param scene a pointer towards the scene
     * @param UIposition a indicator of the X position to place the heart in on the screen
     */
    Heart(QGraphicsScene * scene, int UIposition);

    /**
     * @brief updateHeart updates the heart visibility
     * @param show
     */
    void updateHeart(bool show);
    int getXPosition() const;
};

#endif // HEART_H
