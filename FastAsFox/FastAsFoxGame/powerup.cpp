#include "powerup.h"

PowerUp::PowerUp()
{
    int random=getRandom();
    powerUpType = PowerUpType(random);

    Sprite=new QPixmap(":/fruits/sprites/fruits/fruits.png");


}


void PowerUp::onCollide(){
    int deux =1+1;
}

void PowerUp::applyEffect(){

}

