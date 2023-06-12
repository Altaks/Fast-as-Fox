#include "animatedsprite.h"
#include "constants.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsColorizeEffect>


Fox::Fox(QGraphicsScene *parentScene) : QGraphicsPixmapItem(nullptr),
      walkSpriteSheet(new QPixmap(":/fox/sprites/fox/walk.png")),
      runSpriteSheet(new QPixmap(":/fox/sprites/fox/run.png")), // Updated paths to resources, assuming Qt resources are being used
      scene(parentScene), // Updated paths to resources, assuming Qt resources are being used
      timer(new QTimer(this)),
      elapsedTimer(new QElapsedTimer()),
      currentFrameWalk(0),
      currentFrameRun(0),
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

    colorizeEffect = new QGraphicsColorizeEffect(this);
    this->setGraphicsEffect(colorizeEffect);
    originalColor = QColor();
}

void Fox::updateFrame() {
    int msSinceLastFrame = elapsedTimer->elapsed();

    if (msSinceLastFrame >= 50) {  // 50 ms corresponds to 20 FPS
        QPixmap *currentSpriteSheet = isRunning ? runSpriteSheet : walkSpriteSheet;

        if(isRunning)
        {
            QRect frameRect(currentFrameRun * RUN_SPRITE_WIDTH, 0, RUN_SPRITE_WIDTH, RUN_SPRITE_HEIGHT);
            this->setPixmap(currentSpriteSheet->copy(frameRect));

            this->update(); // Request redraw

            if (currentFrameRun == RUN_SPRITE_N_OF_FRAME - 1) {
                currentFrameRun = 0;
            } else {
                currentFrameRun++;
            }
        }
        else
        {
            QRect frameRect(currentFrameWalk * WALK_SPRITE_WIDTH, 0, WALK_SPRITE_WIDTH, WALK_SPRITE_HEIGHT);

            this->setPixmap(currentSpriteSheet->copy(frameRect));

            this->update(); // Request redraw

            if (currentFrameWalk == WALK_SPRITE_N_OF_FRAME - 1) {
                currentFrameWalk = 0;
            } else {
                currentFrameWalk++;
            }
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

void Fox::setColor(QColor color) {
    colorizeEffect->setColor(color);
}
void Fox::resetColor() {
    colorizeEffect->setColor(originalColor);
}
