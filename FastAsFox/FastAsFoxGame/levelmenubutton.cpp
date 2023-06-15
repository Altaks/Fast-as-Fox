#include "levelmenubutton.h"

LevelMenuButton::LevelMenuButton(QPixmap pixmap, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(pixmap, parent) {}

void LevelMenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit golevelMenu();
}
