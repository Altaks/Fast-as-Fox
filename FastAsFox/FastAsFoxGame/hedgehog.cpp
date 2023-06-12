#include "hedgehog.h"
#include "constants.h"
#include "qgraphicsscene.h"
#include "qtimer.h"
#include <iostream>
#include <random>

Hedgehog::Hedgehog(QGraphicsScene *parentScene, std::pair<int,int> spawnPosition) : QGraphicsPixmapItem(nullptr)
{
    walkSpriteSheet = new QPixmap(HEDGEHOG_WALK);
    attackSpriteSheet = new QPixmap(HEDGEHOG_ATTACK);
    scene = parentScene;
    timer = new QTimer();
    elapsedTimer = new QElapsedTimer();
    walkCurrentFrame = 0;
    attackCurrentFrame = 0;
    attacking = false;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, 1);

    goingRight = distr(eng);

    if(goingRight)
        speed = 1;
    else
        speed = -1;

    this->spritePosition = {spawnPosition.first*32, scene->height() - spawnPosition.second*32 + TILE_SIZE - HEDGEHOG_WALK_SPRITE_HEIGHT};

    setPos(this->spritePosition.first,this->spritePosition.second);
    scene->addItem(this);
    connect(timer, &QTimer::timeout, this, &Hedgehog::updateFrame);
    timer->start(50);
    elapsedTimer->start();
}



void Hedgehog::updateFrame()
{
    int msSinceLastFrame = elapsedTimer->elapsed();

    if (msSinceLastFrame >= 50) {  // 50 ms corresponds to 20 FPS

        if(!attacking)
        {
            QRect frameRect(walkCurrentFrame * HEDGEHOG_WALK_SPRITE_WIDTH, 0, HEDGEHOG_WALK_SPRITE_WIDTH, HEDGEHOG_WALK_SPRITE_HEIGHT);
            this->setPixmap(walkSpriteSheet->copy(frameRect));

            this->update(); // Request redraw

            if (walkCurrentFrame == HEDGEHOG_N_OF_FRAME - 1) {
                walkCurrentFrame = 0;
            } else {
                walkCurrentFrame++;
            }
        }
        else
        {
            QRect frameRect(attackCurrentFrame * HEDGEHOG_ATTACK_SPRITE_WIDTH, 0, HEDGEHOG_ATTACK_SPRITE_WIDTH, HEDGEHOG_ATTACK_SPRITE_HEIGHT);

            this->setPixmap(attackSpriteSheet->copy(frameRect));

            this->update(); // Request redraw

            if (attackCurrentFrame == HEDGEHOG_N_OF_FRAME - 1) {
                attackCurrentFrame = 0;
                attacking=false;
            } else {
                attackCurrentFrame++;
            }
        }



        // Reset the timer to start counting again from this frame.
        elapsedTimer->restart();
    }
}

std::pair<int, int> Hedgehog::getSpritePosition() const
{
    return this->spritePosition;
}

void Hedgehog::updatePosition()
{
    this->spritePosition.first+=speed;
    this->setPos(this->spritePosition.first,this->spritePosition.second);
}

QGraphicsScene *Hedgehog::getScene() const
{
    return this->scene;
}

void Hedgehog::changeDirection()
{
    this->goingRight=!this->goingRight;
    this->speed*=-1;
}

void Hedgehog::setAttacking(bool newAttacking)
{
    attacking = newAttacking;
}
