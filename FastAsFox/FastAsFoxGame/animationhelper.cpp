#include "animationhelper.h"

AnimationHelper::AnimationHelper(QGraphicsItem *item, QObject *parent)
    : QObject(parent), m_item(item) {}

QPointF AnimationHelper::pos() const {
    return m_item->pos();
}

void AnimationHelper::setPos(const QPointF &pos) {
    m_item->setPos(pos);
}
