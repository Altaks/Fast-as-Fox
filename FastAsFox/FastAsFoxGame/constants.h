#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>
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

#define SPIKE         ":/spike/sprites/spike/spikes.png"

#define FRUITS        ":/fruits/sprites/fruits/fruits.png"

#define GROUND_TILES  ":/texture/sprites/texture/TX Tileset Ground.png"

#define HEART         ":/texture/sprites/texture/heart.png"

const std::string LEVEL_ONE = ":/level/level/level1.json";
const std::string LEVEL_TWO = ":/level/level/level2.json";
const std::string LEVEL_THREE = ":/level/level/level3.json";
const std::string LEVEL_FOUR = ":/level/level/level4.json";
const std::string LEVEL_FIVE = ":/level/level/level5.json";

const std::vector<std::string> LEVELS = {LEVEL_ONE,
                                         LEVEL_TWO,
                                         LEVEL_THREE,
                                         LEVEL_FOUR,
                                         LEVEL_FIVE};

// ----------------------------------------------------- //


// ----------------< POWER UPS/DOWN CONSTANTS >------------------ //
const static std::string DASH =             ":/powerups/sprites/powerups/apple.png" ;
const static std::string DOUBLE_JUMP =      ":/powerups/sprites/powerups/cerise.png";
const static std::string CHRONO_FREEZE =    ":/powerups/sprites/powerups/raisin.png";
const static std::string HEALTH =           ":/powerups/sprites/powerups/peche.png" ;
const static std::string SPEED =            ":/powerups/sprites/powerups/citron.png";

const static std::string SLOW  =            ":/powerdowns/sprites/powerdowns/banana.png";
const static std::string TOO_FAST  =        ":/powerdowns/sprites/powerdowns/stawberry.png";
const static std::string BUMP  =            ":/powerdowns/sprites/powerdowns/watermelon.png";
const static std::string INVIS  =           ":/powerdowns/sprites/powerdowns/avocado.png";
const static std::string EXPLOOOSION  =     ":/powerdowns/sprites/powerdowns/pepper.png";

const double DASH_BOOST_PERCENTAGE = 170;
const double DASH_DURATION = 2;

const double SPEED_BOOST_PERCENTAGE = 100;
const double SPEED_DURATION = 5;

const double SLOW_DEBUFF_PERCENTAGE = 50; // -20% of speed
const double SLOW_DURATION = 5;

const double TOOFAST_DEBUFF_PERCENTAGE = 200;
const double TOOFAST_DEBUFF_DURATION = 2;

const std::vector<std::pair<int, int>> LEVEL_ONE_POWERUPDOWNS_POSITIONS = {
    {12, 6}, {12, 8}
};

// ----------------------------------------------------- //

// ----------------< LEVEL POSITION CONSTANTS >--------- //
const std::pair<int,int> LEVEL_ONE_START_POS = std::pair(1,7);
const std::pair<int,int> LEVEL_TWO_START_POS = std::pair(10,35);
const std::pair<int,int> LEVEL_THREE_START_POS = std::pair(1,15);
const std::pair<int,int> LEVEL_FOUR_START_POS = std::pair(1,15);
const std::pair<int,int> LEVEL_FIVE_START_POS = std::pair(2,7);

const std::vector<std::pair<int,int>> LEVEL_START_POS = {LEVEL_ONE_START_POS,
                                                         LEVEL_TWO_START_POS,
                                                         LEVEL_THREE_START_POS,
                                                         LEVEL_FOUR_START_POS,
                                                         LEVEL_FIVE_START_POS};

// ----------------< HEDGEHOG POSITION CONSTANTS >------ //
const std::pair<int,int> HEDGEHOG_LEVEL_ONE_POS1 = std::pair(7,4);
const std::pair<int,int> HEDGEHOG_LEVEL_ONE_POS2 = std::pair(30,10);
const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_ONE_POS_VECTOR = {HEDGEHOG_LEVEL_ONE_POS1,HEDGEHOG_LEVEL_ONE_POS2};


const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_TWO_POS_VECTOR = {};

const std::pair<int,int> HEDGEHOG_LEVEL_THREE_POS1 = std::pair(20,16);
const std::pair<int,int> HEDGEHOG_LEVEL_THREE_POS2 = std::pair(90,14);
const std::pair<int,int> HEDGEHOG_LEVEL_THREE_POS3 = std::pair(115,14);
const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_THREE_POS_VECTOR = {HEDGEHOG_LEVEL_THREE_POS1,HEDGEHOG_LEVEL_THREE_POS2,HEDGEHOG_LEVEL_THREE_POS3};

const std::pair<int,int> HEDGEHOG_LEVEL_FOUR_POS1 = std::pair(44,12);
const std::pair<int,int> HEDGEHOG_LEVEL_FOUR_POS2 = std::pair(70,14);
const std::pair<int,int> HEDGEHOG_LEVEL_FOUR_POS3 = std::pair(99,20);
const std::pair<int,int> HEDGEHOG_LEVEL_FOUR_POS4 = std::pair(135,14);
const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_FOUR_POS_VECTOR = {HEDGEHOG_LEVEL_FOUR_POS1,
                                                                       HEDGEHOG_LEVEL_FOUR_POS2,
                                                                       HEDGEHOG_LEVEL_FOUR_POS3,
                                                                       HEDGEHOG_LEVEL_FOUR_POS4};


const std::vector<std::pair<int,int>> HEDGEHOG_LEVEL_FIVE_POS_VECTOR = {};

const std::vector<std::vector<std::pair<int,int>>> HEDGEHOG_POS = {HEDGEHOG_LEVEL_ONE_POS_VECTOR,
                                                                   HEDGEHOG_LEVEL_TWO_POS_VECTOR,
                                                                   HEDGEHOG_LEVEL_THREE_POS_VECTOR,
                                                                   HEDGEHOG_LEVEL_FOUR_POS_VECTOR,
                                                                   HEDGEHOG_LEVEL_FIVE_POS_VECTOR};

// ----------------< SPIKE POSITION CONSTANTS >--------- //
const std::pair<int,int> SPIKE_LEVEL_ONE_POS1 = std::pair(41,6);
const std::pair<int,int> SPIKE_LEVEL_ONE_POS2 = std::pair(60,5);
const std::vector<std::pair<int,int>> SPIKE_LEVEL_ONE_POS_VECTOR = {SPIKE_LEVEL_ONE_POS1,SPIKE_LEVEL_ONE_POS2};


const std::vector<std::pair<int,int>> SPIKE_LEVEL_TWO_POS_VECTOR = {SPIKE_LEVEL_ONE_POS1,SPIKE_LEVEL_ONE_POS2};

const std::pair<int,int> SPIKE_LEVEL_THREE_POS1 = std::pair(39,15);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS2 = std::pair(40,15);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS3 = std::pair(53,14);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS4 = std::pair(54,14);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS5 = std::pair(126,13);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS6 = std::pair(134,13);
const std::pair<int,int> SPIKE_LEVEL_THREE_POS7 = std::pair(145,13);
const std::vector<std::pair<int,int>> SPIKE_LEVEL_THREE_POS_VECTOR = {SPIKE_LEVEL_THREE_POS1,
                                                                     SPIKE_LEVEL_THREE_POS2,
                                                                     SPIKE_LEVEL_THREE_POS3,
                                                                     SPIKE_LEVEL_THREE_POS4,
                                                                     SPIKE_LEVEL_THREE_POS5,
                                                                     SPIKE_LEVEL_THREE_POS6,
                                                                     SPIKE_LEVEL_THREE_POS7};

const std::pair<int,int> SPIKE_LEVEL_FOUR_POS1 = std::pair(34,14);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS2 = std::pair(63,14);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS3 = std::pair(85,18);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS4 = std::pair(109,18);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS5 = std::pair(110,18);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS6 = std::pair(111,18);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS7 = std::pair(112,18);
const std::pair<int,int> SPIKE_LEVEL_FOUR_POS8 = std::pair(113,18);
const std::vector<std::pair<int,int>> SPIKE_LEVEL_FOUR_POS_VECTOR = {SPIKE_LEVEL_FOUR_POS1,
                                                                    SPIKE_LEVEL_FOUR_POS2,
                                                                    SPIKE_LEVEL_FOUR_POS3,
                                                                    SPIKE_LEVEL_FOUR_POS4,
                                                                    SPIKE_LEVEL_FOUR_POS5,
                                                                    SPIKE_LEVEL_FOUR_POS6,
                                                                    SPIKE_LEVEL_FOUR_POS7,
                                                                    SPIKE_LEVEL_FOUR_POS8};


const std::vector<std::pair<int,int>> SPIKE_LEVEL_FIVE_POS_VECTOR = {SPIKE_LEVEL_ONE_POS1,SPIKE_LEVEL_ONE_POS2};


const std::vector<std::vector<std::pair<int,int>>> SPIKE_POS = {SPIKE_LEVEL_ONE_POS_VECTOR,
                                                                SPIKE_LEVEL_TWO_POS_VECTOR,
                                                                SPIKE_LEVEL_THREE_POS_VECTOR,
                                                                SPIKE_LEVEL_FOUR_POS_VECTOR,
                                                                SPIKE_LEVEL_FIVE_POS_VECTOR};

// ----------------< END BERRIES POSITION CONSTANTS >-- //
const std::pair<int,int> END_BERRIES_LEVEL1 = std::pair(71,7);
const std::pair<int,int> END_BERRIES_LEVEL2 = std::pair(71,7);
const std::pair<int,int> END_BERRIES_LEVEL3 = std::pair(148,14);
const std::pair<int,int> END_BERRIES_LEVEL4 = std::pair(147,14);
const std::pair<int,int> END_BERRIES_LEVEL5 = std::pair(71,7);

const std::vector<std::pair<int,int>> END_BERRIES = {END_BERRIES_LEVEL1,
                                                     END_BERRIES_LEVEL2,
                                                     END_BERRIES_LEVEL3,
                                                     END_BERRIES_LEVEL4,
                                                     END_BERRIES_LEVEL5};


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


const int HEART_1 = 2;
const int HEART_2 = 3;
const int HEART_3 = 4;

const short MAX_COLOR=7;


#define COLLISION_OFFSET 8
#define COLLISION_OFFSET_ENTIITY 8

#endif // CONSTANTS_H
