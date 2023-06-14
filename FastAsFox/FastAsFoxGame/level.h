#ifndef LEVEL_H
#define LEVEL_H

#include "berriespile.h"
#include "hedgehog.h"
#include "spike.h"
#include <QPair>
#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QLCDNumber>
#include <cmath>
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QHBoxLayout>



using namespace std;

#include "player.h"
#include "gameobject.h"
#include "map.h"
#include "heart.h"


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
    std::string lcdCount;
    QTimer * timer;
    std::vector<Hedgehog *>* hedgehogs;
    std::vector<Spike *>* spikes;
    std::vector<Heart *>* hearts;

private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void playerCollidesSpike();
    void levelOverByDeath();
    void changeHeartDisplay();
    void updateHeartPosition();

public:
    Level(pair<int,int> startingPosition, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    Map * getMap();
    void showLCD();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;
    bool levelCleared;

public slots:
    void finish();
    std::string getLcdCount();

};


#endif // LEVEL_H
