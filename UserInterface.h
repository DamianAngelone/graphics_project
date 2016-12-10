#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Structure.h"

class UserInterface {
public:
	static void drawUI();	// Draw the user interface
	static void setCalculatingScore(bool n);	//Controls the state where the time bonus is calculated
	static void incrScore();    			// Increases the global score
	static void decrScore(int n);    		// Decreases the global score
	static void decrTime();					// Decrease global time
	static void setTime(); 					// Sets the global time
	static void gameOver();					// Function for the Game Over state
	static void levelLost();				// Function for the Level Lost state
	static void finishedLevel();			// Function for the Finished Level state
	static void setGameOverState();			// Controls Game Over state
	static void setFinishedLevelState();	// Controls Finished Level state
	static void setLevelState();			// Controls Level Lost state
	static void setWinGameState();			// Controls Win Game state
	static void setIntroState();			// Controls Intro state
	static void readHighScore();			// Reads the high score to the text file
	static void writeHighScore();			// Writes the high score to the text file

	static bool getGameOverState();			// If the game is in Game Over state or not
	static bool getLevelState();			// If the game is in Level Lost state or not	
	static bool getWinGameState();			// If the game is in Win Game state or not
	static bool getFinishedLevelState();	// If the game is in Finished Level state or not
	static bool getIntroState();			// If the game is in Intro state or not
	static bool calculatingScore();			// Calculates the time bonus

	static int getScore();		// Gets global score.
	static int getTime();   	// Gets global time.
};

#endif