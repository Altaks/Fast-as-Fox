#include "berry.h"
#include <random>

using namespace std;

Berry::Berry()
{

}


int Berry::generateRandom(){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(1,5);

    return distr(eng);
}

void Berry::onCollide(Player * player){
    QRect berry(x, y, TILE_SIZE, TILE_SIZE);

    QRect playerRect(player->getAnimation()->x(),player->getAnimation()->y(),player->getAnimation()->pixmap().width(),player->getAnimation()->pixmap().height());

    if (GameObject::collides(berry, playerRect) != std::pair<std::optional<CollisionSide>,std::optional<CollisionSide>>(std::nullopt, std::nullopt)){
        player->setActualBerry(this);
    }
}

void Berry::applyEffect(Player * player){
}
