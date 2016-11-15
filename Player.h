#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:	
	struct point3D {
		float x, y, z;
	};
	static point3D getCoor();				// Get x, y, z of where the player is
	static void setRotation(int change);	// Set the rotation of the player
	static void drawPlayer(bool step);		// Get x, y, z of where the player is
};

#endif