#include "fox.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>


Fox::Fox(QGraphicsScene *parentScene, QGraphicsView *parentView)
    : QGraphicsPixmapItem(nullptr),
      scene(parentScene),
      view(parentView), // store reference to the view
      walkSpriteSheet(new QPixmap(":/fox/sprites/fox/walk.png")), // Updated paths to resources, assuming Qt resources are being used
      runSpriteSheet(new QPixmap(":/fox/sprites/fox/run.png")), // Updated paths to resources, assuming Qt resources are being used
      stopSpriteSheet(new QPixmap(":/fox/sprites/fox/modfox.png")),
      timer(new QTimer(this)),
      elapsedTimer(new QElapsedTimer()),
      currentFrame(0),
      isRunning(false),
      spritePosition(QPointF(0, 0)),
      spriteVelocity(QPointF(0, 0)),
      isStopped(false)
{
    // Check if pixmap loaded correctly
    if(walkSpriteSheet->isNull() || runSpriteSheet->isNull() || stopSpriteSheet->isNull()) {
        qWarning() << "Failed to load spritesheet.";
    }

    setPos(spritePosition);
    scene->addItem(this);
    connect(timer, &QTimer::timeout, this, &Fox::updateFrame);
    timer->start(50);
    elapsedTimer->start();

    if (spritePosition.x() > view->width() / 4.0) {
        // Center the view slightly to the right of the fox to keep the fox offset to the left.
        view->centerOn(QPointF(spritePosition.x() + view->width() / 4.0, spritePosition.y()));
    }

}

void Fox::updateFrame() {
    int msSinceLastFrame = elapsedTimer->elapsed();

    if (msSinceLastFrame >= 50) {  // 50 ms corresponds to 20 FPS
        QPixmap *currentSpriteSheet;
        int frameWidth;
        int totalFrames;

        if (isStopped) {
            currentSpriteSheet = stopSpriteSheet;
            frameWidth = stopSpriteSheet->width() / 16; // modfox.png has 16 frames horizontally
            totalFrames = 16;
        } else {
            currentSpriteSheet = isRunning ? runSpriteSheet : walkSpriteSheet;
            frameWidth = isRunning ? 78 : 78;
            totalFrames = currentSpriteSheet->width() / frameWidth;
        }

        QRect frameRect(currentFrame * frameWidth, 0, frameWidth, currentSpriteSheet->height());
        this->setPixmap(currentSpriteSheet->copy(frameRect));

        if (!isStopped) {
            spriteVelocity += gravity;

            if (isRunning) {
                spritePosition.rx() += 10;  // Increase horizontal speed when running
            } else {
                spritePosition.rx() += 5;  // Default horizontal speed
            }

            spritePosition += spriteVelocity;

            QPointF proposedPosition = spritePosition;

            if (isRunning) {
                proposedPosition += QPointF(10, 0);  // Increase horizontal speed when running
            } else {
                proposedPosition += QPointF(1, 0);  // Default horizontal speed
            }

            proposedPosition += spriteVelocity;

            int rightEdgeOfMap = scene->width() - this->pixmap().width();

            if (proposedPosition.x() >= rightEdgeOfMap) {
                proposedPosition.setX(0);  // Set the x-position back to start
                spriteVelocity.setX(0);  // Reset horizontal velocity

                qDebug() << "Fox has reached the right edge of the map, resetting position.";
            }

            spritePosition = proposedPosition;
            this->setPos(spritePosition);
            this->update(); // Request redraw

            if (spritePosition.y() > groundLevel) {
                spritePosition.setY(groundLevel);
                spriteVelocity.setY(0);
            }

            if (spritePosition.x() > view->width() / 4.0) {
                // Center the view slightly to the right of the fox to keep the fox offset to the left.
                view->centerOn(QPointF(spritePosition.x() + view->width() / 4.0, spritePosition.y()));
            }

        }

        if (currentFrame == totalFrames - 1) {
            currentFrame = 0;
        } else {
            currentFrame++;
        }

        // Reset the timer to start counting again from this frame.
        elapsedTimer->restart();
    }
}




void Fox::stopMoving() {
    spriteVelocity.setX(0);
    isStopped = true;
}

void Fox::startMoving() {
    isStopped = false;
}

void Fox::moveTo(int x, int y) {
    setPos(x - boundingRect().width() / 2, y - boundingRect().height() / 2);
}
