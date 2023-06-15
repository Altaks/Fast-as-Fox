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
#include "heart.h"
#include "hublot.h"


class Level : public QObject
{
    Q_OBJECT
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    GameObject * endingObject;
    Player * player;
    Map * map;
    int level;
    void loadMap();
    void showMap();
    void showScore();
    void initLCD();
    QGraphicsScene * scene;
    QGraphicsView * view;
    QMainWindow * mwindow;
    double count;
    QTimer * timer;
    std::vector<Hedgehog *>* hedgehogs;
    std::vector<Spike *>* spikes;
    std::vector<Heart *>* hearts;
    Hublot * hublot;
    QLCDNumber* lcd;
    QTime* time;
    QTimer* timerLCD;


private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void playerCollidesSpike();
    void levelOverByDeath();
    void changeHeartDisplay();
    void updateHeartPosition();

public:
    Level(int leveln, pair<int,int> startingPosition,  Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    void finish();
    Map * getMap();
    void showLCD();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;
    void updateHublot();
};


#endif // LEVEL_H
