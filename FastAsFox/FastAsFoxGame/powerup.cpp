#include "powerup.h"

PowerUp::PowerUp(QGraphicsScene * scene,Level * levels)
{
    int random=generateRandom();
    powerUpType = PowerUpType(random);

    level=levels;

    switch (powerUpType){
    case Dash:
    {
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/apple.png");
        break;
    }
    case Double_Jump:
    {
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/cerise.png");
        break;
    }
    case ChronoFreeze:
    {
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/raisin.png");
        break;
    }
    case Speed:
    {
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/citron.png");
        break;
    }
    case Revive:
    {
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/peche.png");
        break;
    }
    default:
        BerriesSprite=new QPixmap(":/powerUp/sprites/powerUp/apple.png");
        break;
    }
    this->berries = new GameObject();
    theScene=scene;
    QRect placement(0,0,TILE_SIZE,TILE_SIZE);
    this->berries->setRectangle(placement);

    int graphicsX;
    int graphicsY;

    for(Tile * tile : *level->getMap()->getActuallyLoadedTiles()){
        if(tile->getTileId()==100){ // or tile->getTileId()==261 or tile->getTileId()==262 or tile->getTileId()==263 or tile->getTileId()==264){
            graphicsX = abs(tile->getX()) * TILE_SIZE;
            graphicsY = (this->level->getMap()->getSections().at(0)->getSectionHeight() - tile->getY()) * TILE_SIZE;

            *BerriesSprite=BerriesSprite->scaled(320,320);
            setPixmap(*BerriesSprite);
            setPos(graphicsX, graphicsY);
            setZValue(1);
            scene->addItem(this);
            update();
            break;
        }
    }
    if(BerriesSprite->isNull()) {
        qInfo() << "suuuuuu \n";
    }
}

PowerUp::~PowerUp()
{
}

void PowerUp::onCollide(GameObject* obj){
}

void PowerUp::applyEffect(Player *player){
    qInfo() << "Berry's eaten \n";
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

