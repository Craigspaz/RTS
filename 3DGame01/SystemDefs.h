#ifndef _SYSTEM_DEFS_H
#define _SYSTEM_DEFS_H
/*Stores Global Constants*/

static int TEXTUREWIDTH = 32; //This can change if resolution changes
static int TEXTUREHEIGHT = 32; //This can change if resolution changes

#define RANK_01 1
#define RANK_02 2
#define RANK_03 3
#define RANK_04 4
#define RANK_05 5
#define RANK_06 6
#define RANK_07 7
#define RANK_08 8
#define RANK_09 9

#define DEFAULT_TANK_HEALTH 25
#define DEFAULT_RANK RANK_01


#define GRASS 0
#define DIRT 1
#define WATER 2
#define MOUNTAIN 3
#define BRIDGE 4


#define BUILDER_TYPE 0
#define SOLDIER_TYPE 1
#define TANK_TYPE 2


#define TEST_BUIDING_ID 0
#define TEST_BUIDING_BARRACKS_ID 1
#define BRIDGE_ID 2

#define NEUTRAL_FACTION -1
#define FACTION1 0
#define FACTION2 1




static int worldWidth;
static int worldHeight;

#endif