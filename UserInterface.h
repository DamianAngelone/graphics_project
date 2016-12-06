#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Structure.h"

class UserInterface {
public:
	static void drawUI();		// Draw the user interface
	static void incrScore();    // Increases the global score
	static void decrScore();    // Decreases the global score
	static int getScore();		// Gets global score.
	static void decrTime();		// Decrease global time.
	static int getTime();   	// Gets global time.
};

#endif