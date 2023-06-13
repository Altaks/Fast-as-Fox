#ifndef LEVEL_H
#define LEVEL_H

#include "hedgehog.h"
#include "spike.h"
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
    std::vector<Hedgehog *>* hedgehogs;
    std::vector<Spike *>* spikes;

private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void playerCollidesSpike();
    void levelOverByDeath();

public:
    Level(pair<int,int> startingPosition, GameObject * endingObject, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    void finish();
    Map * getMap();
    void showUI();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;
};


#endif // LEVEL_H
