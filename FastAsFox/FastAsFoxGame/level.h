#ifndef LEVEL_H
#define LEVEL_H

#include <QPair>

using namespace std;

#include "player.h"
#include "map.h"

class Level
{
private:
    pair<int,int> startingPosition;
    pair<int,int> endingPosition;
    Player * player;
    Map map;
    void loadMap();
    void showMap();
    void showScore();
    void showUI();
public:
<<<<<<< Updated upstream
    Level(pair<int,int> startingPosition, pair<int,int> endingPosistion/*,Map map*/);
=======
    Level(pair<int,int> startingPosition, pair<int,int> endingPosistion,Map map);
>>>>>>> Stashed changes
    ~Level();
    void start();
    void finish();
    Map getMap();
    void setPlayer(Player* Aplayer);
};


#endif // LEVEL_H
