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

void Berry::onCollide(GameObject* obj){
}

void Berry::applyEffect(Player * player){

}
