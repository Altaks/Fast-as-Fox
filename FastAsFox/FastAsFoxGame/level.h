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



using namespace std;

#include "player.h"
#include "map.h"
#include "heart.h"

class Berry;

class Level : public QObject
{
    Q_OBJECT
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    BerriesPile * endingObject;
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
    bool levelCleared;
    QTimer * playerUpdatePositionClock;
    QTimer * hedgehogUpdatePositionClock;
    QLCDNumber* lcd;
    QTime* time;
    QTimer* timerLCD;
    std::vector<Berry *> * berries;

private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void playerCollidesSpike();
    void levelOverByDeath();
    void changeHeartDisplay();
    void updateHeartPosition();
    void finish();
    void playerCollidesBerries();

public slots:
    void updateLCDPosition();

public:
    Level(int leveln, pair<int,int> startingPosition,  Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    Map * getMap();
    void showLCD();
    void setPlayer(Player * Aplayer);
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;
    bool getLevelCleared() const;
    QTimer *getTimerLCD() const;
    void setTimerLCD(QTimer *newTimerLCD);
    double getCount() const;
    void setCount(double newCount);
    signals:
    void updateHeartsDisplay();

};


#endif // LEVEL_H
