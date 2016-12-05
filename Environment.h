#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Structure.h"

class Environment {
public:	
	static void drawEnvironment(int step);	// Get x, y, z of where the player is
	static bool touchingSand(int x, float y, int z);	// Check if the player is touching the sand
};

#endif