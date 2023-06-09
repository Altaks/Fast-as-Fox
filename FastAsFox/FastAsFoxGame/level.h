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
    /**
     * @brief timescore the value of the timer at the top-ight corner of the screen
     */
    QElapsedTimer timescore;
    /**
     * @brief startingPosition the starting position of the player
     */
    pair<int,int> startingPosition;
    BerriesPile * endingObject;
    Player * player;
    /**
     * @brief map the map that represents the level
     */
    Map * map;
    /**
     * @brief loadMap loads the map
     */
    void loadMap();
    /**
     * @brief showMap displays the map on screen
     */
    void showMap();
    /**
     * @brief showScore displays the player's score
     */
    void showScore();
    /**
     * @brief initLCD initialize the timer display
     */
    void initLCD();
    /**
     * @brief scene the scene of the level
     */
    QGraphicsScene * scene;
    /**
     * @brief view the camera
     */
    QGraphicsView * view;
    /**
     * @brief mwindow the window in which the level is displayed
     */
    QMainWindow * mwindow;
    /**
     * @brief lcd the display of the timer
     */
    QLCDNumber * lcd;
    /**
     * @brief count
     */
    double count;
    /**
     * @brief timer the value of the timer
     */
    QTimer * timer;
    std::string lcdCount;



private slots:
    void updateLCD();

public:
    /**
     * @brief Level the constructor for the level class
     * @param startingPosition the starting position of the player
     * @param endingObject the objective to reach for the level to end
     * @param AMap the map of the level
     * @param mainwindow the window of the program (in which to display the level)
     */
    Level(pair<int,int> startingPosition, Map * AMap, QMainWindow * mainwindow);
    ~Level();
    /**
     * @brief start loads and shows the map, the level, and the timer
     */
    void start();

    /**
     * @brief getMap getter for the level's map
     * @return the level's map
     */
    Map * getMap();
    /**
     * @brief showUI shows the user interface
     */
    void showUI();
    /**
     * @brief updateLCDPosition updates the timer's position
     */
    void updateLCDPosition();
    /**
     * @brief setPlayer stter fot eh level's player
     * @param Aplayer the player to be set as the level's player
     */
    void setPlayer(Player * Aplayer);
    Player * getPlayer();
    GameObject * getEndingObject();

public slots:
    void finish();
    std::string getLcdCount();
};


#endif // LEVEL_H
