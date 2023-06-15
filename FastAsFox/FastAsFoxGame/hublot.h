#ifndef HUBLOT_H
#define HUBLOT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>

class Hublot : public QGraphicsPixmapItem {
    QGraphicsScene *scene;
    int squareSize;

public:
    explicit Hublot(QGraphicsScene *scene);
    void updateHublot(bool show);

private:
    void setupImage();
};

#endif // HUBLOT_H
