#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Structure.h"

class Environment {
public:	
	static void drawEnvironment(int step);	// Get x, y, z of where the player is
	static void drawBoard();	//Draws the board the game takes place on
	static void setTextures();		//Draws the textures on the wall
};

#endif