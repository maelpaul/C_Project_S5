#ifndef __WORLDALGO_H__
#define __WORLDALGO_H__

#include "world.h"

#define ACHIEV 2

// Function used to get indexes from coordinates
int coord_to_idx(unsigned int i, unsigned int j, unsigned int w);

// Function used to initialize randomly a world
struct world world_init(int fill);

// Function used to display a frame of the world
void world_disp(struct world *w);

// Constant representing the different colors values
enum color
{
	BLACK = 0,
	WHITE = 16777215,
	RED = 255,
	GREEN = 65280,
	BLUE = 16711680,
	YELLOW = 65535,
	GREY = 9868950,
	NEUTRAL = 4294967295,
	NOT_BLACK = NEUTRAL - 1,
	NOT_GREY = NEUTRAL - 2
};

#endif