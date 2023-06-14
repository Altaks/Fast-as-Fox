#include "level.h"
#include "QtCore/qtimer.h"
#include <cmath>
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QHBoxLayout>


Level::Level(pair<int,int> AStartingPosition, Map * AMap, QMainWindow* mainwindow) : QObject()
{
    levelCleared = false;
    startingPosition=AStartingPosition;
    map=AMap;
    scene = map->getScene();
    player = new Player(map, AStartingPosition, nullptr);
    map->setItsPlayer(player);
    player->setInAir(true);
    map->setItsPlayer(player);
    scene = map->getScene();
    mwindow=mainwindow;
    pair<int,int>endpose(70,5);
    endingObject=new BerriesPile(scene,endpose,map->getSections().at(0)->getSectionHeight());
    count=0.00;
    hedgehogs = new std::vector<Hedgehog*>();

    QTimer * playerUpdatePositionClock = new QTimer();
    QTimer * hedgehogUpdatePositionClock = new QTimer();


    for(int i=0; i<HEDGEHOG_LEVEL_ONE_POS_VECTOR.size(); i++)
    {
        hedgehogs->push_back(new Hedgehog(scene,HEDGEHOG_LEVEL_ONE_POS_VECTOR.at(i)));
        connect(hedgehogUpdatePositionClock, &QTimer::timeout, hedgehogs->at(i), &Hedgehog::updatePosition);

        connect(hedgehogs->at(i), &Hedgehog::playerLoseHealth, player, &Player::updateHealthbar);
    }
    connect(hedgehogUpdatePositionClock, &QTimer::timeout, this, &Level::changeHedgehogsDirection);

    connect(playerUpdatePositionClock, &QTimer::timeout, player, &Player::updatePosition);

    connect(playerUpdatePositionClock, &QTimer::timeout, this, &Level::playerCollidesHedgehog);

    connect(player, &Player::playerDeath, this, &Level::levelOverByDeath);

    playerUpdatePositionClock->start(10); // 100 tps
    hedgehogUpdatePositionClock->start(20); // 50 tps
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
            if(hedgehogs->at(i)->getAttacking())
            {
                if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_RUN_SPRITE_WIDTH + COLLISION_OFFSET and
                    player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_ATTACK_SPRITE_WIDTH - COLLISION_OFFSET and
                    player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_RUN_SPRITE_HEIGHT and
                    player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_ATTACK_SPRITE_HEIGHT)
                        hedgehogs->at(i)->setAttacking(true);
                else
                        hedgehogs->at(i)->setAttacking(false);
            }
            else
            {
                if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_RUN_SPRITE_WIDTH + COLLISION_OFFSET and
                    player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_WALK_SPRITE_WIDTH - COLLISION_OFFSET and
                    player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_RUN_SPRITE_HEIGHT and
                    player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_WALK_SPRITE_HEIGHT)
                        hedgehogs->at(i)->setAttacking(true);
                else
                        hedgehogs->at(i)->setAttacking(false);
            }
        }
        else
        {
            if(hedgehogs->at(i)->getAttacking())
            {
                if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_WALK_SPRITE_WIDTH + COLLISION_OFFSET and
                    player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_ATTACK_SPRITE_WIDTH - COLLISION_OFFSET and
                    player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_WALK_SPRITE_HEIGHT and
                    player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_ATTACK_SPRITE_HEIGHT)
                        hedgehogs->at(i)->setAttacking(true);
                else
                        hedgehogs->at(i)->setAttacking(false);
            }
            else
            {
                if(player->getSpritePosition().first > hedgehogs->at(i)->getSpritePosition().first - FOX_WALK_SPRITE_WIDTH + COLLISION_OFFSET and
                    player->getSpritePosition().first < hedgehogs->at(i)->getSpritePosition().first + HEDGEHOG_WALK_SPRITE_WIDTH - COLLISION_OFFSET and
                    player->getSpritePosition().second > hedgehogs->at(i)->getSpritePosition().second - FOX_WALK_SPRITE_HEIGHT and
                    player->getSpritePosition().second < hedgehogs->at(i)->getSpritePosition().second + HEDGEHOG_WALK_SPRITE_HEIGHT)
                        hedgehogs->at(i)->setAttacking(true);
                else
                        hedgehogs->at(i)->setAttacking(false);
            }
        }
    }
}

void Level::levelOverByDeath()
{
   hedgehogs->at(-1);
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
    timer = new QTimer();

    // Connect timer's timeout() signal to the slot that will update the LCD
    connect(timer, &QTimer::timeout, this, &Level::updateLCD);

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
    lcd->setFrameStyle(0);  // This removes the frame

    // Setting the color of the LCD to white
    QPalette lcdpalette;
    lcdpalette.setColor(QPalette::WindowText, Qt::white);
    lcdpalette.setColor(QPalette::Window, Qt::black); // set the background color to black
    lcd->setAutoFillBackground(true); // this will allow the background color to show
    lcd->setPalette(lcdpalette);

    // Initialize the GIF
    QLabel *gifLabel = new QLabel(mwindow);
    QMovie *movie = new QMovie(":/userInterface/sprites/userInterface/sablier.gif");

    gifLabel->setMovie(movie);
    movie->start();

    // Place the GIF in the top right corner
    gifLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

    // If you need to set a specific size for the GIF label
    gifLabel->setFixedSize(100, 100);  // adjust dimensions as needed
}

void Level::updateLCD()
{

    // Increment counter by 0.01 (which corresponds to hundredths of a second)
    count += 0.01;

    // Round the number to two decimal places
    double roundedCount = std::round(count * 100.0) / 100.0;

    // Format the number as a string with leading zeroes
    QString str = QString("%1").arg(roundedCount, 5, 'f', 2, '0');
    lcdCount = str.toStdString();

    // Display the formatted string
    lcd->display(str);
    map->setLcdCount(lcdCount);

}

void Level::updateLCDPosition()
{
    int margin = 10;
    lcd->move(mwindow->width() - lcd->width() - margin, margin);
}

void Level::showUI()
{
    showScore();
}

void Level::start(){
    loadMap();
    showMap();
    initLCD();
    showUI();
}

void Level::finish(){

    if(endingObject->isAtTheEnd(player->getAnimation())==true && !levelCleared){
        map->displayAnimation();
        this->levelCleared = true;
    }
}

Map * Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}

GameObject * Level::getEndingObject(){
    return endingObject;
}

Player * Level::getPlayer(){
    return player;
}

std::string Level::getLcdCount()
{
    return lcdCount;
}

QLCDNumber* Level::getLCD(){
    return lcd;
}
