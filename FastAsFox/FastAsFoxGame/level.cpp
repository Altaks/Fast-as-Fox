#include "level.h"

Level::Level(pair<int,int> AStartingPosition, pair<int,int> AnEndingPosistion, Map * AMap)
{
    startingPosition=AStartingPosition;
    endingPosition=AnEndingPosistion;
    map=AMap;
}

Level::~Level(){
    player=nullptr;
    map= nullptr;
}


void Level::loadMap(){
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

Map* Level::getMap(){
    return map;
}

void Level::setPlayer(Player* Aplayer){
    player=Aplayer;
}

