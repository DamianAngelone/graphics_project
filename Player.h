#ifndef PLAYER_H
#define PLAYER_H

#include "Structure.h"

class Player {
public:
	static Structure::point3D getCoor();				// Get x, y, z of where the player is
	static void setRotation(int change);	// Set the rotation of the player
	static void reset();					// Reset the player's position
	static void drawPlayer(bool step);		// Get x, y, z of where the player is
};

#endif