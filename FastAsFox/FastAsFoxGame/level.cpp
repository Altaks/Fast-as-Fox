#include "level.h"

Level::Level(pair<int,int> AStartingPosition, pair<int,int> AnEndingPosistion,Map AMap)
{
    startingPosition=AStartingPosition;
    endingPosition=AnEndingPosistion;
    map=AMap;
}

Level::~Level(){
    player=nullptr;
    endingPosition=nullptr;
}


void Level::loadMap(){
    map.load();
}

void Level::showMap(){
    map.display();
}

void Level::showScore(){

}

void Level::showUI(){
    showScore();
}

void Level::start(){
    loadMap();
    showMap();
    showUI();
}

void Level::finish(){

}

Map Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}

