#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Structure.h"

class UserInterface {
public:
	static void drawUI();		// Draw the user interface
	static void incrScore();    // Increases the global score
	static void decrScore(int n);    // Decreases the global score
	static void decrTime();		// Decrease global time.
	static void setTime(); 
	static void gameOver();
	static void setCalculatingScore(bool n);
	static void levelLost();
	static void finishedLevel();
	static void setGameOverState();
	static void setFinishedLevelState();
	static void setLevelState();
	static void setWinGameState();
	static void setIntroState();
	static void readHighScore();
	static void writeHighScore();

	static bool getGameOverState();
	static bool getLevelState();
	static bool getWinGameState();
	static bool getFinishedLevelState();
	static bool getIntroState();
	static bool calculatingScore();

	static int getScore();		// Gets global score.
	static int getTime();   	// Gets global time.
};

#endif