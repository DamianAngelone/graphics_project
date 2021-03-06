#ifndef INTERACTIVITY_H
#define INTERACTIVITY_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Structure.h"
#include "Enemy.h"

class Interactivity {
public:
	static Enemy enemy[2];			// the enemy array, 2 enemies

	static void draw(bool step);
	static void setSpace(int n);	
	static void setLevel(int n);
	static void incrLevel();
	static void checkIntersections();			// Check to see if the player is on the same block as an enemy
	static void setLives(int n);				// Set the number of lives the player has

	static GLubyte* loadPPM(char* file, int* width, int* height, int* maxi);	// Load a ppm file
	
	static int getSpace();	
	static int getLives();	
	static int getLevel();						// Get the level
	static int getLength();						// Get the number of blocks in a row
	static int getBeenTo();						// Get amount of blocks visited in the current level
	static int getAmountOfBlocks();             // Get amount of blocks in current level.

	static float getTheta();					// Get the angle of rotation
	
	static Structure::point3D getEye();			// The first 3 paramters of gluLookAt
	static Structure::point3D getCenter();		// The 4-6 parameters of gluLookAt
	static Structure::point3D* getPlayerBeen();	// Get what spots the player has been to
	/**
		Record that the player has landed on a spot
		@param x  -> The x position of the object
		@param y  -> The y position of the object
		@param z  -> The z position of the object
	**/
	static void pushPosition(int x, int z);					
	/**
		Callback function for glut's keyboard func
		@param key -> ASCII character that was press
		@param x   -> Where the cursor was when the key was pressed
		@param y   -> Where the cursor was when the key was pressed
	**/	
	static void keyboard(unsigned char key, int x, int y);
	/**
		Callback function for glut's keyboard func
		@param key -> ASCII character that was press
		@param x   -> Where the cursor was when the key was pressed
		@param y   -> Where the cursor was when the key was pressed
	**/
	static void special(int key, int x, int y);
	static void printInstructions();			// Prints the instructions to the console

};

#endif