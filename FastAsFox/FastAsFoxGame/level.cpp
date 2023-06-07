#include "level.h"

Level::Level(pair<int,int> AStartingPosition, GameObject * endingObject,Map* AMap)
{
    startingPosition=AStartingPosition;
    endingObject=AnEndingObject;
    map=AMap;
    fox=AFox;
}

Level::~Level(){
    delete player;
    delete endingObject;
    delete map;
    delete fox;
}


void Level::loadMap(){
    map->load();
}

void Level::showMap(){
    map->getScene();
    map->getView();
}

void Level::start(){
    loadMap();
    showMap();
}

void Level::finish(){

}

Map Level::getMap(){
    return *map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}

