#ifndef INTERACTIVITY_H
#define INTERACTIVITY_H

class Interactivity {
public:	
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
	static void special(unsigned char key, int x, int y);
	/**
		Prints the instructions to the console
	**/
	static void printInstructions();
};

#endif