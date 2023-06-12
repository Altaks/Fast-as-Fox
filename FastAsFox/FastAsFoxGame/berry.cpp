#include "berry.h"
#include <random>

using namespace std;

Berry::Berry()
{

}


int Berry::getRandom(){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(1,5);

    return distr(eng);
}

void Berry::onCollide(){
    int deux = 1+1;
}

void Berry::applyEffect(){

}
