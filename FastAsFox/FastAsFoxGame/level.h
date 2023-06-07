#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>
#include <QElapsedTimer>


using namespace std;

#include "player.h"
#include "gameobject.h"
#include "map.h"

class Level
{
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    GameObject * endingPosition;
    Player * player;
    Map map;
    void loadMap();
    void showMap();
    void showScore();
    void showUI();
public:
    Level(pair<int,int> startingPosition, GameObject * endingPosistion, Map AMap);
    ~Level();
    void start();
    void finish();
    Map getMap();
    void setPlayer(Player* Aplayer);
};


#endif // LEVEL_H
