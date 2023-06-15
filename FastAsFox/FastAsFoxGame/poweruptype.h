#ifndef POWERUPTYPE_H
#define POWERUPTYPE_H

#include <iostream>

#include <QPixmap>

const static std::string DASH =          ":/powerups/sprites/powerups/apple.png" ;
const static std::string DOUBLE_JUMP =   ":/powerups/sprites/powerups/cerise.png";
const static std::string CHRONO_FREEZE = ":/powerups/sprites/powerups/raisin.png";
const static std::string HEALTH =        ":/powerups/sprites/powerups/peche.png" ;
const static std::string SPEED =         ":/powerups/sprites/powerups/citron.png";

enum PowerUpType {
    SPEED_TYPE, DASH_TYPE, CHRONOFREEZE_TYPE, HEALTH_TYPE, DOUBLE_JUMP_TYPE
};

#endif // POWERUPTYPE_H
