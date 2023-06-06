#include "level.h"

Level::Level(pair<int,int> AStartingPosition, GameObject * AnEndingPosistion, Map AMap)
{
    startingPosition=AStartingPosition;
    endingPosition=AnEndingPosistion;
    map=AMap;
}

Level::~Level(){
    player=nullptr;
}


void Level::loadMap(){
    map.load();
}

void Level::showMap(){

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

