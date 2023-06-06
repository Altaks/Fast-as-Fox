#include "AnimatedSprite.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>

AnimatedSprite::AnimatedSprite(QObject *parent)
    : GameObject(parent), currentFrame(0), spritePosition(QPointF(0, 0))
{
    // Create and connect the timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AnimatedSprite::updateAnimation);
    timer->start(50);
}


void AnimatedSprite::updatePosition() {
    if (isRunning) {
        spritePosition.rx() += 10;  // Increase horizontal speed when running
    } else {
        spritePosition.rx() += 1;  // Default horizontal speed
    }

    setPos(spritePosition);
}

void AnimatedSprite::updateAnimation() {
    int msSinceLastFrame = elapsedTimer->elapsed();

    if (msSinceLastFrame >= 50) {  // 50 ms corresponds to 20 FPS
        QPixmap *currentSpriteSheet = isRunning ? &runSpriteSheet : &walkSpriteSheet;
        int frameWidth = isRunning ? 78 : 78;
        int totalFrames = currentSpriteSheet->width() / frameWidth;

        QRect frameRect(currentFrame * frameWidth, 0, frameWidth, 78);
        spriteSheet->operator= (currentSpriteSheet->copy(frameRect));

        if (currentFrame == totalFrames - 1) {
            currentFrame = 0;
        } else {
            currentFrame++;
        }

        // Reset the timer to start counting again from this frame.
        elapsedTimer->restart();
    }
}

void AnimatedSprite::setIsRunning(bool newIsRunning) {
    isRunning = newIsRunning;
}
