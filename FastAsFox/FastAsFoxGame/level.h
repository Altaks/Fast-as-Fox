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
    /**
     * @brief timescore the timer of elapsed time from the starting of the level
     */
    QElapsedTimer timescore;

    /**
     * @brief startingPosition the starting coordinates of the player
     */
    pair<int,int> startingPosition;

    /**
     * @brief endingObject a pointer towards the ending object to check for collisions
     */
    BerriesPile * endingObject;

    /**
     * @brief player a pointer towards the player
     */
    Player * player;

    /**
     * @brief map a pointer towards the currently loaded map
     */
    Map * map;

    /**
     * @brief level the level index
     */
    int level;
    void loadMap();
    void showMap();
    void showScore();
    void initLCD();

    /**
     * @brief scene the scene that is linked to the displayed view
     */
    QGraphicsScene * scene;

    /**
     * @brief view the view that will be displayed
     */
    QGraphicsView * view;

    /**
     * @brief mwindow a pointer towards the window
     */
    QMainWindow * mwindow;
    double count;
    QTimer * timer;

    /**
     * @brief hedgehogs a vector that contains every hedgedog in the level
     */
    std::vector<Hedgehog *>* hedgehogs;

    /**
     * @brief spikes a vector that contains every spike in the level
     */
    std::vector<Spike *>* spikes;

    /**
     * @brief hearts a vector that contains every heart that is displayed
     */
    std::vector<Heart *>* hearts;
    bool levelCleared;
    QTimer * playerUpdatePositionClock;
    QTimer * hedgehogUpdatePositionClock;
    QLCDNumber* lcd;
    QTime* time;
    QTimer* timerLCD;

    /**
     * @brief berries a vector towards every berry that has been loaded in the level
     */
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
    /**
     * @brief Level a constructor
     * @param leveln the index of the level
     * @param startingPosition the starting coordinates of the level
     * @param AMap a pointer towards the loaded map
     * @param mainwindow a pointer towards the main window
     */
    Level(int leveln, pair<int,int> startingPosition,  Map * AMap, QMainWindow * mainwindow);
    ~Level();

    /**
     * @brief start starts the level for the player
     */
    void start();
    Map * getMap();
    /**
     * @brief showLCD displays the time counter
     */
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
    /**
     * @brief updateHeartsDisplay triggers a graphical update of the hearts display
     */
    void updateHeartsDisplay();

};


#endif // LEVEL_H
