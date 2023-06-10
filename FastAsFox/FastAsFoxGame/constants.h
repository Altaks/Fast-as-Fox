﻿#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "qpoint.h"
#include <utility>
#define TILE_SIZE 32

#define PI 3.14159

// ----------------< PHYSICS CONSTANTS >---------------- //
const float gravity = 9.81/100; // to set to 9.81
const double alpha = (2 * PI * ((double)30 / 360)); // 25 is the angle in degrees
const double V0 = 0.2;
// ----------------------------------------------------- //

// ----------------< MOVEMENT CONSTANTS >--------------- //
const double walking_speed = 0.02;
const double running_speed = 0.1;
// ----------------------------------------------------- //

// ----------------< PATHS CONSTANTS >------------------ //
#define FOX_RUN       ":/fox/sprites/fox/run.png"
#define FOX_WALK      ":/fox/sprites/fox/walk.png"
#define FOX_DEAD      ":/fox/sprites/fox/dead.png"
#define FOX_JUMP      ":/fox/sprites/fox/pounce.png"
#define FOX_LAND      ":/fox/sprites/fox/landing.png"
#define FRUITS        ":/fruits/sprites/fruits/fruits.png"
#define GROUND_TILES  ":/texture/sprites/texture/TX Tileset Ground.png"
#define LEVEL_ONE     ":/level/level/level1.json"
#define LEVEL_TWO     ":/level/level/level2.json"
// ----------------------------------------------------- //

// ----------< STARTING POSITION CONSTANTS >------------ //
const std::pair<int,int> LEVEL_ONE_START_POS = std::pair(40,10);
const std::pair<int,int> LEVEL_TWO_START_POS = std::pair(10,35);

const QPointF LEVEL_ONE_START_POS_QPF = QPointF(40,10);

#define COLLISION_OFFSET 5

#endif // CONSTANTS_H
