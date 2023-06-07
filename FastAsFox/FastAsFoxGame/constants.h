#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TILE_SIZE 32 /**< The size of a tile in pixels. */
const float gravity = 9.81; /**< The acceleration due to gravity. */
const int jump_angle = 45; /**< The angle at which the fox jumps. */

#define FOX_RUN ":/fox/sprites/fox/run.png" /**< The file path to the running fox sprite sheet. */
#define FOX_WALK ":/fox/sprites/fox/walk.png" /**< The file path to the walking fox sprite sheet. */
#define FOX_DEAD ":/fox/sprites/fox/dead.png" /**< The file path to the dead fox sprite. */
#define FOX_JUMP ":/fox/sprites/fox/pounce.png" /**< The file path to the jumping fox sprite. */
#define FOX_LAND ":/fox/sprites/fox/landing.png" /**< The file path to the landing fox sprite. */

#define FRUITS ":/fruits/sprites/fruits/fruits.png" /**< The file path to the fruits sprite sheet. */
#define GROUND_TILES ":/texture/sprites/texture/TX Tileset Ground.png" /**< The file path to the ground tiles sprite sheet. */
#define LEVEL_ONE ":/level/level/level1.json" /**< The file path to the first level configuration file. */

#define DEFAULT_FONT ":/font/sprites/font/font.TTF" /**< The file path to the font used. */

#define COLLISION_OFFSET 5 /**< The offset used for collision detection. */

#endif // CONSTANTS_H
