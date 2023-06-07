#include "level.h"
#include "QtCore/qtimer.h"

Level::Level(pair<int,int> AStartingPosition, GameObject * AnEndingObject, Map * AMap, Fox * AFox, MainWindow* mainwindow)
{
    startingPosition=AStartingPosition;
    endingObject=AnEndingObject;
    map=AMap;
    fox=AFox;
    mwindow=mainwindow;
}

Level::~Level(){
    delete player;
    delete endingObject;
    delete map;
    delete fox;
}


void Level::loadMap(){
    map->load();
}

void Level::showMap(){
    scene = map->getScene();
    view = map->getView();
    this->mwindow->setCentralWidget(view);
}

void Level::showScore()
{
    // Initialize the LCD number
    lcd = new QLCDNumber();
    lcd->setDigitCount(7);  // 2 digits for integer part, 1 dot, 2 digits for fraction part
    lcd->setMode(QLCDNumber::Dec);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->display(count);

    int margin = 10;
    // Set LCD size and location
    lcd->setFixedSize(200, 50); // Adjust the size as per your requirements
    lcd->move(mwindow->width() - lcd->width() - margin, margin);


    // Initialize the timer
    timer = new QTimer();

    // Connect timer's timeout() signal to the slot that will update the LCD
    connect(timer, &QTimer::timeout, this, &Level::updateLCD);


    // Start the timer to fire every 10 ms (this will result in hundredths of a second)
    timer->start(10);
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

void Level::showUI()
{
    showScore();
}

void Level::start(){
    loadMap();
    showMap();
}

void Level::finish(){

}

Map * Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}

