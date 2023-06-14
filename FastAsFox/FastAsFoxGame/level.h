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
#include "coin.h"
#include "hedgehog.h"


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
    std::vector<Coin*> levelCoins;
    std::vector<std::pair<int, int>> coinPositions;
    int coinScore;
    QLabel* coinLabel;

private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void levelOverByDeath();
    void handleCoinCollected();

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
    void setCoinScore(int newCoinScore);
    int getCoinScore() const;
    void increaseCoinScore(int amount);
    void addCoinsToLevel();
};


#endif // LEVEL_H
