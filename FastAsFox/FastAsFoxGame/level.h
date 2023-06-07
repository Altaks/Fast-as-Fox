#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>
#include <QElapsedTimer>
#include <QLabel>

using namespace std;

#include "player.h"
#include "gameobject.h"
#include "map.h"

class Level
{
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    GameObject * endingObject;
    Player * player;
    Fox * fox;
    Map * map;
    void loadMap();
    void showMap();

public:
    Level(pair<int,int> startingPosition, GameObject * endingObject, Map * AMap, Fox * fox);
    ~Level();
    void start();
    void finish();
    Map * getMap();
    void setPlayer(Player * Aplayer);
};


#endif // LEVEL_H
