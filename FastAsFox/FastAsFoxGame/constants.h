#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "qpoint.h"
#include <utility>
#define TILE_SIZE 32

// ----------------< PHYSICS CONSTANTS >---------------- //
const float gravity = 9.81/100; // to set to 9.81
const int alpha = 45;
const double V0 = 0.6;
// ----------------------------------------------------- //

// ----------------< MOVEMENT CONSTANTS >--------------- //
const double walking_speed = 0.1/5;
const double running_speed = 0.2/5;
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


// ----------------< FOX SPRITE SIZE >------------------ //

const int RUN_SPRITE_WIDTH = 72;
const int RUN_SPRITE_HEIGHT = 32;
const int RUN_SPRITE_N_OF_FRAME = 7;

const int WALK_SPRITE_WIDTH = 53;
const int WALK_SPRITE_HEIGHT = 31;
const int WALK_SPRITE_N_OF_FRAME = 9;

// ----------------< MENU WIDGET >------------------ //

const short MAX_COLOR=7;


#define COLLISION_OFFSET 2

#endif // CONSTANTS_H
