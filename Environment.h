#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
public:	
	static float block[8][3];		// The array coordinates to make a cube
	static void drawEnvironment();	// Get x, y, z of where the player is
private:
	static void drawBlock(int a, int b, int c, int d);		// Draws a single block
	static void drawBlocks();		// Draws the platforms for the player/enemies
};

#endif