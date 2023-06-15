#include "gifitem.h"

GifItem::GifItem(const QString &fileName, QGraphicsItem *parent)
    : QGraphicsItem(parent) {
    movie = new QMovie(fileName);

    if (!movie->isValid()) {
        delete movie;
        throw std::invalid_argument("Gif is not valid.");
    }

    if (movie->frameCount() <= 1) {
        delete movie;
        throw std::invalid_argument("This Gif does not have multiple frames.");
    }

    QObject::connect(movie, &QMovie::frameChanged, [this](int frameNumber) {
        Q_UNUSED(frameNumber)
        this->update();
    });

    movie->start();
}

QRectF GifItem::boundingRect() const {
    return QRectF(-movie->frameRect().center(), movie->currentImage().size());
}

void GifItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-movie->frameRect().center(), movie->currentPixmap());
}
