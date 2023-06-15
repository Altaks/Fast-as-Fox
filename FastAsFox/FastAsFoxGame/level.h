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
#include "berriespile.h"

class PowerUp;

class Level : public QObject
{
    Q_OBJECT
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    BerriesPile * endingObject= nullptr;
    Player * player= nullptr;
    Map * map= nullptr;
    void loadMap();
    void showMap();
    void showScore();
    void initLCD();
    QGraphicsScene * scene= nullptr;
    QGraphicsView * view= nullptr;
    QMainWindow * mwindow= nullptr;
    QLCDNumber * lcd= nullptr;
    double count;
    string lcdCount;
    QTimer * timer= nullptr;
    std::vector<Hedgehog *>* hedgehogs= nullptr;
    std::vector<Coin*> levelCoins;
    std::vector<std::pair<int, int>> coinPositions;
    int coinScore;
    QLabel* coinLabel= nullptr;

private slots:
    void updateLCD();
    void changeHedgehogsDirection();
    void playerCollidesHedgehog();
    void levelOverByDeath();
    void handleCoinCollected();

public:
    Level(pair<int,int> startingPosition, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    void start();
    Map * getMap();
    void showUI();
    void updateLCDPosition();
    void setPlayer(Player * Aplayer);
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;

    QLCDNumber* getLCD();
    bool levelCleared;

    void setCoinScore(int newCoinScore);
    int getCoinScore() const;
    void increaseCoinScore(int amount);
    void addCoinsToLevel();

public slots:
    void finish();
    std::string getLcdCount();
};


#endif // LEVEL_H
