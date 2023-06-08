#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TILE_SIZE 32

// ----------------< PHYSICS CONSTANTS >---------------- //
const float gravity = 9.81/20; // to set to 9.81
const int alpha = 45;
const double V0 = 0.6;
// ----------------------------------------------------- //

// ----------------< MOVEMENT CONSTANTS >--------------- //
const double walking_speed = 0.1;
const double running_speed = 0.5;
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
// ----------------------------------------------------- //

#define COLLISION_OFFSET 5

#endif // CONSTANTS_H
