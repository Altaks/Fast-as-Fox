#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>
#include <QElapsedTimer>
#include <QLabel>
#include "mainwindow.h"


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
    Fox * fox;
    Map * map;
    void loadMap();
    void showMap();
    void showScore();
    QGraphicsScene * scene;
    QGraphicsView * view;
    MainWindow * mwindow;
    QLCDNumber * lcd;
    double count;
    QTimer * timer;

private slots:
    void updateLCD();

public:
    Level(pair<int,int> startingPosition, GameObject * endingObject, Map * AMap, Fox * fox, MainWindow * mainwindow);
    ~Level();
    void start();
    void finish();
    Map * getMap();
    void showUI();
    void setPlayer(Player * Aplayer);
};


#endif // LEVEL_H
