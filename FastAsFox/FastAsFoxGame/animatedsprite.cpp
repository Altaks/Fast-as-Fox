#include "animatedsprite.h"
#include "constants.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

Fox::Fox(QGraphicsScene *parentScene) : QGraphicsPixmapItem(nullptr),
      walkSpriteSheet(new QPixmap(":/fox/sprites/fox/walk.png")),
      runSpriteSheet(new QPixmap(":/fox/sprites/fox/run.png")), // Updated paths to resources, assuming Qt resources are being used
      scene(parentScene), // Updated paths to resources, assuming Qt resources are being used
      timer(new QTimer(this)),
      elapsedTimer(new QElapsedTimer()),
      currentFrame(0),
      isRunning(false),
      spritePosition(LEVEL_ONE_START_POS)
{
    // Check if pixmap loaded correctly
    if(walkSpriteSheet->isNull() || runSpriteSheet->isNull()) {
        qWarning() << "Failed to load spritesheet.";
    }

    setPos(spritePosition.first,spritePosition.second);
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

        QPixmap coloredPlayer = this->pixmap().copy();
        coloredPlayer.fill(Qt::red);
        this->setPixmap(coloredPlayer);
        this->setZValue(1);


        this->update(); // Request redraw

        if (currentFrame == totalFrames - 1) {
            currentFrame = 0;
        } else {
            currentFrame++;
        }

        // Reset the timer to start counting again from this frame.
        elapsedTimer->restart();
    }
}

void Fox::startRunning()
{
    this->isRunning = true;
}


std::pair<int, int> Fox::getSpritePosition() const {
    return this->spritePosition;
}

bool Fox::getIsRunning() const
{
    return isRunning;
}

void Fox::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}

QGraphicsScene *Fox::getScene() const
{
    return scene;
}

