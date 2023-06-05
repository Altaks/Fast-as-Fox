#include "level.h"

Level::Level(pair<int,int> AStartingPosition, pair<int,int> AnEndingPosistion,Map AMap)
{
    startingPosition=AStartingPosition;
    endingPosition=AnEndingPosistion;
    map=AMap;
}

Level::~Level(){

}


void Level::loadMap(){

}

void Level::showMap(){

}

void Level::showScore(){

}

void Level::showUI(){

}

void Level::start(){

}

void Level::finish(){

}

Map Level::getMap(){
    return map;
}
