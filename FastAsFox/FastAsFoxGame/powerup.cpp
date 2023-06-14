#include "powerup.h"

PowerUp::PowerUp(QGraphicsScene * scene,Level * level)
{
    int random=generateRandom();
    powerUpType = PowerUpType(random);

    BerriesSprite=new QPixmap(":/fruits/sprites/fruits/fruits.png");
    int x;
    switch (powerUpType){
    case Dash:
    {
        x=TILE_SIZE;
    }
    case Double_Jump:
    {
        x=14*TILE_SIZE;
    }
    case ChronoFreeze:
    {
        x=3*TILE_SIZE;
    }
    case Speed:
    {
        x=18*TILE_SIZE;
    }
    case Revive:
    {
        x=12*TILE_SIZE;
    }
    default:
        break;
    }
    this->berries =new GameObject();
    scene=theScene;
    QRect placement(x,0,TILE_SIZE,TILE_SIZE);
    this->berries->setRectangle(placement);

    int graphicsX;
    int graphicsY;

    for(Tile * tile : *level->getMap()->getActuallyLoadedTiles()){
        if(tile->getTileId()==260 || tile->getTileId()==261 || tile->getTileId()==262 || tile->getTileId()==263 || tile->getTileId()==264){
            graphicsX=tile->getX();
            graphicsY=tile->getY();
            setPos(graphicsX, graphicsY);
            scene->addItem(this);
            *BerriesSprite=BerriesSprite->scaled(32,32);
            this->setPixmap(*BerriesSprite);
            this->update();
        }
    }
}



void PowerUp::onCollide(GameObject* obj){
}

void PowerUp::applyEffect(Player *player){
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
            player->setInAir(true);
            player->playerJumped();
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

            break;
        }
        case Revive:
        {
            player->addHP();
            break;
        }
        default:
            break;
    }

}

