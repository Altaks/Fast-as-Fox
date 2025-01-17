﻿#include "level.h"
#include "QtCore/qtimer.h"
#include "powerup.h"
#include <QGridLayout>

Level::Level(int leveln, pair<int,int> AStartingPosition, Map * AMap, QMainWindow* mainwindow) : QObject()
{
    startingPosition=AStartingPosition;
    map=AMap;
    level = leveln;
    player = new Player(map, AStartingPosition);
    endingObject = new BerriesPile(map->getScene(),END_BERRIES.at(level),map->getScene()->height());
    player->setInAir(true);
    map->setItsPlayer(player);
    scene = map->getScene();
    mwindow=mainwindow;
    levelCleared = false;
    count=0.00;
    hedgehogs = new std::vector<Hedgehog*>();
    spikes = new std::vector<Spike*>();
    hearts = new std::vector<Heart*>();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Level::updateLCD);
    connect(timer, &QTimer::timeout, this, &Level::updateLCDPosition);

    hearts->push_back(new Heart(scene,HEART_1));
    hearts->push_back(new Heart(scene,HEART_2));
    hearts->push_back(new Heart(scene,HEART_3));

    for(Heart * heart : *hearts){
        heart->setZValue(2);
    }

    playerUpdatePositionClock = new QTimer();
    hedgehogUpdatePositionClock = new QTimer();

    for(int i=0; i<HEDGEHOG_POS.at(level).size(); i++)
    {
        hedgehogs->push_back(new Hedgehog(scene,HEDGEHOG_POS.at(level).at(i)));
        connect(hedgehogUpdatePositionClock, &QTimer::timeout, hedgehogs->at(i), &Hedgehog::updatePosition);
        connect(hedgehogs->at(i), &Hedgehog::playerLoseHealth, player, &Player::updateHealthbar);
        connect(hedgehogs->at(i), &Hedgehog::playerLoseHealth, this, &Level::changeHeartDisplay);

    }

    for(int i=0; i<SPIKE_POS.at(level).size(); i++)
    {
        spikes->push_back(new Spike(scene,SPIKE_POS.at(level).at(i)));
        connect(spikes->at(i), &Spike::playerLoseHealth, player, &Player::updateHealthbar);
        connect(spikes->at(i), &Spike::playerLoseHealth, this, &Level::changeHeartDisplay);
    }

    connect(hedgehogUpdatePositionClock, &QTimer::timeout, this, &Level::changeHedgehogsDirection);
    connect(playerUpdatePositionClock, &QTimer::timeout, this, &Level::updateHeartPosition);
    connect(playerUpdatePositionClock, &QTimer::timeout, player, &Player::updatePosition);
    connect(playerUpdatePositionClock, &QTimer::timeout, this, &Level::playerCollidesHedgehog);
    connect(playerUpdatePositionClock, &QTimer::timeout, this, &Level::playerCollidesSpike);
    connect(playerUpdatePositionClock, &QTimer::timeout, this, &Level::playerCollidesBerries);
    connect(player, &Player::playerDeath, this, &Level::levelOverByDeath);


    playerUpdatePositionClock->start(10); // 100 tps
    hedgehogUpdatePositionClock->start(20); // 50 tps

    QSize mapViewSize = map->getView()->size();
    QPixmap background(":/texture/sprites/texture/bg.jpg");
    scene->setBackgroundBrush(background.scaled(mapViewSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    connect(this, &Level::updateHeartsDisplay, this, &Level::changeHeartDisplay);


    this->berries = new std::vector<Berry *>();
    for(std::pair<int, int> coordinates : POWERUPDOWNS_POS.at(level)){
            this->berries->push_back(Berry::generateRandom(scene, coordinates));
        }


}

void Level::playerCollidesBerries(){
    for(Berry * berry : *this->berries){
        // check for collision, and if it collides, use the onCollide function
        QRect berryRect = QRect(berry->x(), berry->y(), berry->pixmap().width(), berry->pixmap().height());
        QRect playerRect = QRect(this->player->getAnimation()->x(),this->player->getAnimation()->y(),this->player->getAnimation()->pixmap().width(), this->player->getAnimation()->pixmap().height());

        if(berryRect.intersects(playerRect)){
            berry->onCollide(this->player);
        }
    }
}

Level::~Level(){
    delete player;
    delete endingObject;
    delete map;
}

Player *Level::getPlayer() const
{
    return player;
}

QGraphicsScene *Level::getScene() const
{
    return scene;
}

double Level::getCount() const
{
    return count;
}

void Level::setCount(double newCount)
{
    count = newCount;
}


QGraphicsView *Level::getView() const
{
    return view;
}

void Level::changeHedgehogsDirection()
{
    for(int i=0; i<hedgehogs->size(); i++)
    {
        std::pair<int,int> hedgehogTilePosition = hedgehogs->at(i)->getSpritePosition();
        std::pair<int,int> testTilePosition = hedgehogs->at(i)->getSpritePosition();

        hedgehogTilePosition.first = hedgehogTilePosition.first/32;
        hedgehogTilePosition.second = scene->height()/32 - hedgehogTilePosition.second/32;

        testTilePosition.first=hedgehogTilePosition.first;
        testTilePosition.second=hedgehogTilePosition.second-1;
        if(map->getMap()->at(0)->getCoordinatesToTileId()->at(testTilePosition)==0)
            hedgehogs->at(i)->changeDirection();

        testTilePosition.first=hedgehogTilePosition.first+1;
        if(map->getMap()->at(0)->getCoordinatesToTileId()->at(testTilePosition)==0)
            hedgehogs->at(i)->changeDirection();

        testTilePosition.first=hedgehogTilePosition.first;
        testTilePosition.second=hedgehogTilePosition.second;
        if(map->getMap()->at(0)->getCoordinatesToTileId()->at(testTilePosition)!=0)
            hedgehogs->at(i)->changeDirection();

        testTilePosition.first=hedgehogTilePosition.first+1;
        if(map->getMap()->at(0)->getCoordinatesToTileId()->at(testTilePosition)!=0)
            hedgehogs->at(i)->changeDirection();
    }
}

void Level::playerCollidesHedgehog()
{
    for(int i=0; i<hedgehogs->size(); i++)
    {
        if(player->getAnimation()->getIsRunning())
        {
            if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_RUN_SPRITE_WIDTH + COLLISION_OFFSET_ENTIITY and
                player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_WALK_SPRITE_WIDTH - COLLISION_OFFSET_ENTIITY and
                player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_RUN_SPRITE_HEIGHT and
                player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_WALK_SPRITE_HEIGHT)
                hedgehogs->at(i)->setAttacking(true);
            else
                hedgehogs->at(i)->setAttacking(false);
        }
        else
        {
            if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_WALK_SPRITE_WIDTH + COLLISION_OFFSET_ENTIITY and
                player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_WALK_SPRITE_WIDTH - COLLISION_OFFSET_ENTIITY and
                player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_WALK_SPRITE_HEIGHT and
                player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_WALK_SPRITE_HEIGHT)
                hedgehogs->at(i)->setAttacking(true);
            else
                hedgehogs->at(i)->setAttacking(false);
        }
    }
}

void Level::playerCollidesSpike()
{
    for(int i=0; i<spikes->size(); i++)
    {
        if(player->getSpritePosition().first > spikes->at(i)->getSpritePosition().first - FOX_WALK_SPRITE_WIDTH + COLLISION_OFFSET_ENTIITY and
            player->getSpritePosition().first < spikes->at(i)->getSpritePosition().first + TILE_SIZE - COLLISION_OFFSET_ENTIITY and
            player->getSpritePosition().second > spikes->at(i)->getSpritePosition().second - FOX_WALK_SPRITE_HEIGHT and
            player->getSpritePosition().second < spikes->at(i)->getSpritePosition().second + TILE_SIZE)
            spikes->at(i)->setAttacking(true);
        else
            spikes->at(i)->setAttacking(false);
    }
}

void Level::levelOverByDeath()
{
    player->getAnimation()->setPos(startingPosition.first*32, map->getScene()->height() - startingPosition.second*32);
    player->setHp(3);
    changeHeartDisplay();
    for(Berry * berry : *berries)
    {
        berry->addToScene();
    }
    player->setStockedPowerUp(nullptr);
}

void Level::changeHeartDisplay()
{
    if(player->getHp() == 3)
    {
        hearts->at(2)->updateHeart(true);
        hearts->at(1)->updateHeart(true);
        hearts->at(0)->updateHeart(true);
    }
    else if(player->getHp() == 2)
    {
        hearts->at(2)->updateHeart(false);
        hearts->at(1)->updateHeart(true);
        hearts->at(0)->updateHeart(true);
    }
    else if(player->getHp() == 1)
    {
        hearts->at(2)->updateHeart(false);
        hearts->at(1)->updateHeart(false);
        hearts->at(0)->updateHeart(true);
    }
    else if(player->getHp() == 0)
    {
        hearts->at(2)->updateHeart(false);
        hearts->at(1)->updateHeart(false);
        hearts->at(0)->updateHeart(false);
    }
}

void Level::updateHeartPosition()
{
    for(Heart * heart : *hearts)
    {
        heart->setPos(map->getView()->mapToScene(heart->getXPosition()*TILE_SIZE, TILE_SIZE));
    }
}

void Level::loadMap(){
    map->load();
}

void Level::showMap(){
    view = map->getView();
    mwindow->setCentralWidget(view);

    double gameX = this->startingPosition.first * 32;
    double gameY = this->startingPosition.second * 32;

    gameY = this->map->getScene()->height() - gameY;

    this->player->getAnimation()->setPos(gameX, gameY);
}

void Level::showScore()
{
    // Initialize the timer

    // Connect timer's timeout() signal to the slot that will update the LCD


    // Start the timer to fire every 10 ms (this will result in hundredths of a second)
    timer->start(10);
}

void Level::initLCD()
{
    // Initialize the LCD number
    lcd = new QLCDNumber(mwindow);
    lcd->setDigitCount(7);  // 2 digits for integer part, 1 dot, 2 digits for fraction part
    lcd->setMode(QLCDNumber::Dec);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    // Set LCD size and location
    lcd->setFixedSize(200, 50);
    lcd->display(count);
    lcd->show();
}

bool Level::getLevelCleared() const
{
    return levelCleared;
}

void Level::updateLCD()
{

    // Increment counter by 0.01 (which corresponds to hundredths of a second)
    if(!levelCleared)
        count += 0.01;

    // Round the number to two decimal places
    double roundedCount = std::round(count * 100.0) / 100.0;

    // Format the number as a string with leading zeroes
    QString str = QString("%1").arg(roundedCount, 5, 'f', 2, '0');

    // Display the formatted string
    lcd->display(str);

}

void Level::updateLCDPosition()
{
    int margin = 10;
    lcd->move(mwindow->width() - lcd->width() - margin, margin);
}

void Level::showLCD()
{
    showScore();
}

void Level::start(){
    loadMap();
    showMap();
    initLCD();
    updateLCDPosition();
    timer->start(10);
}

void Level::finish(){
    if(endingObject->isAtTheEnd(player->getAnimation())==true && !levelCleared){
            map->displayAnimation(this);
            this->levelCleared = true;
            playerUpdatePositionClock->stop();
            hedgehogUpdatePositionClock->stop();
            for(Hedgehog * hedgehog : *hedgehogs)
                hedgehog->getTimer()->stop();
            player->getAnimation()->getTimer()->stop();
        }
}

Map * Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}
