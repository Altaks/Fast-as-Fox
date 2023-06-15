#ifndef GIFITEM_H
#define GIFITEM_H

#include <QGraphicsItem>
#include <QMovie>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class GifItem : public QGraphicsItem {
public:
    GifItem(const QString &fileName, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QMovie *movie;
};

#endif // GIFITEM_H
