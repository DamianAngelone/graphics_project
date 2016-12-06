#ifndef INTERACTIVITY_H
#define INTERACTIVITY_H

#include "Structure.h"
#include "Enemy.h"

class Interactivity {
public:
	static Enemy enemy[3];			// the enemy array, 2 enemies
	static void draw(bool step);
	static int getLevel();						// Get the level
	static int getLength();						// Get the number of blocks in a row
	static float getTheta();					// Get the angle of rotation

	static Structure::point3D getEye();			// The first 3 paramters of gluLookAt
	static Structure::point3D getCenter();			// The 4-6 parameters of gluLookAt
	static Structure::point3D* getPlayerBeen();		// Get what spots the player has been to
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