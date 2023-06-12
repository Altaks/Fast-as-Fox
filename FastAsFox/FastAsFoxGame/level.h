#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>
#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QLCDNumber>



using namespace std;

#include "player.h"
#include "gameobject.h"
#include "berriespile.h"
#include "map.h"


class Level : public QObject
{
    Q_OBJECT
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    BerriesPile * endingObject;
    Player * player;
    Map * map;
    void loadMap();
    void showMap();
    void showScore();
    void initLCD();
    QGraphicsScene * scene;
    QGraphicsView * view;
    QMainWindow * mwindow;
    QLCDNumber * lcd;
    double count;
    QTimer * timer;
    std::string lcdCount;



private slots:
    void updateLCD();

public:
    Level(pair<int,int> startingPosition, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    Map * getMap();
    void showUI();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
    Player * getPlayer();
    GameObject * getEndingObject();
    std::string getLcdCount();

public slots:
        void finish();
    
};


#endif // LEVEL_H
