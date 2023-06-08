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
#include "map.h"


class Level : public QObject
{
    Q_OBJECT
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    GameObject * endingObject;
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

private slots:
    void updateLCD();

public:
    Level(pair<int,int> startingPosition, GameObject * endingObject, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    void finish();
    Map * getMap();
    void showUI();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
};


#endif // LEVEL_H
