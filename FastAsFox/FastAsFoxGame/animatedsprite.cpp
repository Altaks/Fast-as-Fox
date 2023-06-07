#include "animatedsprite.h"
#include "constants.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

Fox::Fox(QGraphicsScene *parentScene)
    : QGraphicsPixmapItem(nullptr),
      walkSpriteSheet(new QPixmap(FOX_WALK)),
      runSpriteSheet(new QPixmap(FOX_RUN)),
      scene(parentScene),
      timer(new QTimer(this)),
      elapsedTimer(new QElapsedTimer()),
      currentFrame(0),
      isRunning(false),
      spritePosition(QPointF(0, 0)),
      spriteVelocity(QPointF(0, 0))
{
    // Check if pixmap loaded correctly
    if(walkSpriteSheet->isNull() || runSpriteSheet->isNull()) {
        qWarning() << "Failed to load spritesheet.";
    }

    setPos(spritePosition);
    scene->addItem(this);
    connect(timer, &QTimer::timeout, this, &Fox::updateFrame);
    timer->start(50);
    elapsedTimer->start();
}

void Fox::updateFrame() {
    int msSinceLastFrame = elapsedTimer->elapsed();

    if (msSinceLastFrame >= 50) {  // 50 ms corresponds to 20 FPS
        QPixmap *currentSpriteSheet = isRunning ? runSpriteSheet : walkSpriteSheet;
        int frameWidth = isRunning ? 78 : 78;
        int totalFrames = currentSpriteSheet->width() / frameWidth;

        QRect frameRect(currentFrame * frameWidth, 0, frameWidth, 78);
        this->setPixmap(currentSpriteSheet->copy(frameRect));

        spriteVelocity += gravity;

        if (isRunning) {
            spritePosition.rx() += 10;  // Increase horizontal speed when running
        } else {
            spritePosition.rx() += 1;  // Default horizontal speed
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

        if (currentFrame == totalFrames - 1) {
            currentFrame = 0;
        } else {
            currentFrame++;
        }

        // Reset the timer to start counting again from this frame.
        elapsedTimer->restart();
    }
}

void Fox::addScore()
{
    this->score+=1;
}



