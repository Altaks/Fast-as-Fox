#include "level.h"
#include "QtCore/qtimer.h"

Level::Level(pair<int,int> AStartingPosition, GameObject * AnEndingObject, Map * AMap, QMainWindow* mainwindow) : QObject()
{
    startingPosition=AStartingPosition;
    endingObject=AnEndingObject;
    map=AMap;
    player = new Player(map, AStartingPosition);
    player->setInAir(true);
    map->setItsPlayer(player);
    scene = map->getScene();
    mwindow=mainwindow;
    count=0.00;
    hedgehogs = new std::vector<Hedgehog*>();

    for(int i=0; i<HEDGEHOG_LEVEL_ONE_POS_VECTOR.size(); i++)
    {
        hedgehogs->push_back(new Hedgehog(scene,HEDGEHOG_LEVEL_ONE_POS_VECTOR.at(i)));
    }

    QTimer * playerUpdatePositionClock = new QTimer();

    connect(playerUpdatePositionClock, &QTimer::timeout, player, &Player::updatePosition);

    playerUpdatePositionClock->start(10); // 20 tps
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
}

void Level::updateLCD()
{

    // Increment counter by 0.01 (which corresponds to hundredths of a second)
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

}

Map * Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}
