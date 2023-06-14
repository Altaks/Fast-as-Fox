#ifndef LEVELMENUBUTTON_H
#define LEVELMENUBUTTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class LevelMenuButton : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    LevelMenuButton(QPixmap pixmap, QGraphicsItem *parent = nullptr);

signals:
    void golevelMenu();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // LEVELMENUBUTTON_H
