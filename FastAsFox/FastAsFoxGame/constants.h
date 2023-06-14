#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "qpoint.h"
#include <utility>
#define TILE_SIZE 32
#define PI 3.14159

// ----------------< PHYSICS CONSTANTS >---------------- //
const float GRAVITY = 9.81/100; // to set to 9.81
const double ALPHA = (2 * PI * ((double)30 / 360)); // 25 is the angle in degrees
const double V0 = 0.2;
// ----------------------------------------------------- //

// ----------------< MOVEMENT CONSTANTS >--------------- //
const double WALKING_SPEED = 0.03;
const double RUNNING_SPEED = 0.06;
// ----------------------------------------------------- //

// ----------------< PATHS CONSTANTS >------------------ //
#define FOX_RUN       ":/fox/sprites/fox/run.png"
#define FOX_WALK      ":/fox/sprites/fox/walk.png"
#define FOX_DEAD      ":/fox/sprites/fox/dead.png"
#define FOX_JUMP      ":/fox/sprites/fox/pounce.png"
#define FOX_LAND      ":/fox/sprites/fox/landing.png"

#define HEDGEHOG_WALK               ":/hedgehog/sprites/hedgehog/hedgehog_walk_sprite.png"
#define HEDGEHOG_ATTACK             ":/hedgehog/sprites/hedgehog/hedgehog_attack_sprite.png"
#define HEDGEHOG_WALK_BACKWARD      ":/hedgehog/sprites/hedgehog/hedgehog_walk_sprite_backward.png"
#define HEDGEHOG_ATTACK_BACKWARD    ":/hedgehog/sprites/hedgehog/hedgehog_attack_sprite_backward.png"

#define FRUITS        ":/fruits/sprites/fruits/fruits.png"
#define GROUND_TILES  ":/texture/sprites/texture/TX Tileset Ground.png"
#define LEVEL_ONE     ":/level/level/level1.json"
#define LEVEL_TWO     ":/level/level/level2.json"
// ----------------------------------------------------- //

// ----------< LEVEL POSITION    CONSTANTS >------------ //
const std::pair<int,int> LEVEL_ONE_START_POS = std::pair(2,5);
const std::pair<int,int> LEVEL_TWO_START_POS = std::pair(10,35);

const std::pair<int,int> HEDGEHOG_LEVEL_ONE_POS1 = std::pair(7,2);
const std::pair<int,int> HEDGEHOG_LEVEL_ONE_POS2 = std::pair(30,8);
const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_ONE_POS_VECTOR = {HEDGEHOG_LEVEL_ONE_POS1,HEDGEHOG_LEVEL_ONE_POS2};
// ----------------------------------------------------- //

// ----------------< FOX SPRITE SIZE >------------------ //
const int FOX_RUN_SPRITE_WIDTH = 72;
const int FOX_RUN_SPRITE_HEIGHT = 32;
const int FOX_RUN_SPRITE_N_OF_FRAME = 7;

const int FOX_WALK_SPRITE_WIDTH = 53;
const int FOX_WALK_SPRITE_HEIGHT = 31;
const int FOX_WALK_SPRITE_N_OF_FRAME = 9;
// ----------------------------------------------------- //

// ----------------< HEDGEHOG SPRITE SIZE >------------- //
const int HEDGEHOG_WALK_SPRITE_WIDTH = 34;
const int HEDGEHOG_WALK_SPRITE_HEIGHT = 20;

const int HEDGEHOG_ATTACK_SPRITE_WIDTH = 40;
const int HEDGEHOG_ATTACK_SPRITE_HEIGHT = 28;

// ----------------< PowerUpType's Enum >------------------ //
enum PowerUpType{
    Dash=1,
    Double_Jump=2,
    ChronoFreeze=3,
    Speed=4,
    Revive=5,
};


#define COLLISION_OFFSET 2
const int HEDGEHOG_N_OF_FRAME = 4;
// ----------------------------------------------------- //

// ----------------< AUDIO FILES PATHS >---------------- //
#define AUDIO1       ""
#define AUDIO2       ""
#define AUDIO3       ""
#define AUDIO4       ""
#define AUDIO5       ""
#define AUDIO6       ""
#define AUDIO7       ""
#define AUDIO8       ""
#define AUDIO9       ""
#define AUDIO10      ""
// ----------------------------------------------------- //

#define COLLISION_OFFSET 8

#endif // CONSTANTS_H
