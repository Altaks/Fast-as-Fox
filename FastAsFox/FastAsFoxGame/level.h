#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>
#include <QElapsedTimer>

using namespace std;

#include "player.h"
#include "map.h"

class Level
{
private:
    QElapsedTimer timescore;
    pair<int,int> startingPosition;
    pair<int,int> endingPosition;
    Player * player;
    Map* map;
    void loadMap();
    void showMap();
    void showScore();
    void showUI();
public:
    Level(pair<int,int> startingPosition, pair<int,int> endingPosistion,Map* map);
    ~Level();
    void start();
    void finish();
    Map getMap();
    void setPlayer(Player* Aplayer);
};


#endif // LEVEL_H
