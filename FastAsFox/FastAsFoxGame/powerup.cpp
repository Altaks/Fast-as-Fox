#include "powerup.h"

PowerUp::PowerUp()
{
    int random=getRandom();
    powerUpType = PowerUpType(random);

    BerriesSprite=new QPixmap(":/fruits/sprites/fruits/fruits.png");
    if (BerriesSprite->isNull()==true){
        qDebug("fichier introuvable");
    }
    else {

    }

}


void PowerUp::onCollide(GameObject* obj){
    int deux =1+1;
}

void PowerUp::applyEffect(Player * player, Level * level){
    switch (powerUpType){
        case Dash:
        {
            int playersX=player->getAnimation()->x();
            int playersY=player->getAnimation()->y();
            player->addVelocity(playersX+10,playersY);
            break;
        }
        case Double_Jump:
        {
            break;
        }
        case ChronoFreeze:
        {
            float count=stof(level->getLcdCount())-5;
            level->getLCD()->display(count);
            break;
        }
        case Speed:
        {

        }
        case Revive:
        {
            player->setRevival();

        }
        default:
            break;
    }

}

