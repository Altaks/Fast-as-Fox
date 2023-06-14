#ifndef ANIMATIONHELPER_H
#define ANIMATIONHELPER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>

class AnimationHelper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    AnimationHelper(QGraphicsItem *item, QObject *parent = nullptr);

    QPointF pos() const;
    void setPos(const QPointF &pos);

private:
    QGraphicsItem *m_item;
};

#endif // ANIMATIONHELPER_H
