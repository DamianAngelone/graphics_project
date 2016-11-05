#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:	
	static struct point3D {
		int x, y, z;
	};
	static point3D getCoor();		// Get x, y, z of where the player is
	static void drawPlayer();	// Get x, y, z of where the player is
};

#endif