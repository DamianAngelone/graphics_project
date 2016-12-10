#include "UserInterface.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <cmath>
#include <iostream>
#include <unistd.h>
using namespace std;

// Include project files
#include "Interactivity.h"
#include "Environment.h"

bool gameOverState = false;			// Game Over state
bool gameLevelState = false;		// Level Lost state
bool finishedLevelState = false;	// Level Won state
bool safeToDecreaseTime = false;	// Allow the time to decrease
bool wonGame = false;				// Game Won state
bool intro = true;					// Intro state
bool initalScore = true;			// Initialize Score state

int score = 0;		// Sets starting score
int highScore = 0;	// Sets high score
int gTime = 50;		// Sets clock

char filename[50] = "highscore.txt";	// filename

FILE *fp; // The file to save/load from

/* Sets high scpre from text file */
void UserInterface::readHighScore() {	
	fp = fopen(filename, "r");
	char buf[4];
	fscanf(fp, "%s", buf);
	sscanf(buf, "%d", &highScore);
	fclose(fp);
}
/* Writes new high scpre from text file */
void UserInterface::writeHighScore() {
	if (score > highScore) {
		fp = fopen(filename, "w+");
		char buf[4];
	 	snprintf(buf, sizeof(buf), "%d", score);
	    fputs(buf, fp);
	    fclose(fp);
	}
}
/* Increases score */
void UserInterface::incrScore(){

	score += 1;
}
/* Decreases score */
void UserInterface::decrScore(int n){
	if ((score - n) >= 0)
		score -= n;
	else
		score = 0;
}
/* Score getter */
int UserInterface::getScore(){

	return score;
}
/* Decrease time */
void UserInterface::decrTime(){

	if (gTime > 0)
		gTime -= 1;
}
/* Time getter */
int UserInterface::getTime(){

	return gTime;
}
/* Time setter */
void UserInterface::setTime(){

	gTime = 50;
}
/* Game Over State getter */
bool UserInterface::getGameOverState(){

	return gameOverState;
}
/* Game Over State setter */
void UserInterface::setGameOverState(){

	gameOverState = !gameOverState;
}
/* Win Game State getter */
bool UserInterface::getWinGameState(){

	return wonGame;
}
/* Win Game State setter */
void UserInterface::setWinGameState(){

	wonGame = !wonGame;
}
/* Finished Level State getter */
bool UserInterface::getFinishedLevelState(){

	return finishedLevelState;
}
/* Finished Level State setter */
void UserInterface::setFinishedLevelState(){

	finishedLevelState = !finishedLevelState;
}
/* Lost Level State getter */
bool UserInterface::getLevelState(){

	return gameLevelState;
}
/* Lost Level State setter */
void UserInterface::setLevelState(){

	gameLevelState = !gameLevelState;
}
/* Intro State getter */
bool UserInterface::getIntroState(){

	return intro;
}
/* Intro State getter */
void UserInterface::setIntroState(){

	intro = !intro;
}
/* Calculates time bonus */
bool UserInterface::calculatingScore(){

	return safeToDecreaseTime;
}
/* Controls Calculate Time Bonus state */
void UserInterface::setCalculatingScore(bool m){

	safeToDecreaseTime = m;
}

// Draws any text passed to it
void drawText(string s) {
	void * font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i) {
	    char c = *i;
	    if(c == '.')
	    	break;
	    glutBitmapCharacter(font, c);
	    glutPostRedisplay();
    }
}

// Draws any text passed to it (high score)
void drawHighScore(string s) {
	void * font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i) {
	    char c = *i;
	    if(c == '.')
	    	break;
	    glutBitmapCharacter(font, c);
	    glutPostRedisplay();
    }
}

// Draws any text passed to it (intro text)
void drawText2(string s) {
	void * font = GLUT_BITMAP_HELVETICA_12;
	for (string::iterator i = s.begin(); i != s.end(); ++i) {
	    char c = *i;
	    if(c == '.')
	    	break;
	    glutBitmapCharacter(font, c);
	    glutPostRedisplay();
    }
}
// Draws any text passed to it (State/UI messages)
void drawTextTitles(string s) {
	void * font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i) {
	    char c = *i;
	    if(c == '.')
	    	break;
	    glutBitmapCharacter(font, c);
	    glutPostRedisplay();
    }
}
/* Calculates tim bonus */
void calculateScore(){

	usleep(2000); //added delay to make the animation more fluent
	UserInterface::setCalculatingScore(true);
	UserInterface::decrTime();
	UserInterface::incrScore();
}
/* Controls Finished Level state */
void UserInterface::finishedLevel(){
  	
  	//Calulates score
  	for(int i = 0; i < UserInterface::getTime(); i++){

  		calculateScore();	
	}

	char buf1[5];
	char buf2[5];
	char buf3[5];
	
	double temp1 = Interactivity::getLevel();
	double temp2 = UserInterface::getScore();
	double temp3 = Interactivity::getLives();
	
	snprintf(buf1, sizeof(buf1), "%f", temp1);
	snprintf(buf2, sizeof(buf2), "%f", temp2);
	snprintf(buf3, sizeof(buf3), "%f", temp3);

	string currLevel(buf1);
	string currScore(buf2);
	string currLives(buf3);

	string s[4];
	s[0] = "You Beat Level " + currLevel;
	s[1] = "Current Score: " + currScore;
	s[2] = "Current Lives: " + currLives;
	s[3] = "Press 'R' to continue to next level.";

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 4; i++) {
    	glRasterPos2i(350, ((-i * 20) - 70));
  		drawTextTitles(s[i]);
  	}
}
/* Controls Game Over state */
void UserInterface::gameOver(){

	char buf1[5];
	double temp1 = UserInterface::getScore();
	snprintf(buf1, sizeof(buf1), "%f", temp1);
	string finalScore(buf1);
	string s[3];

	// If player won
	if(wonGame){
		
		for(int i = 0; i < UserInterface::getTime(); i++){
			// Calculates time bonus
  			calculateScore();	
		}

		s[0] = "Game Complete";
		s[1] = "Final Score: " + finalScore;
		s[2] = "Press 'R' to restart game.";

		UserInterface::writeHighScore(); //Writes high score to the text file
	}
	else{
		s[0] = "Game Over";
		s[1] = "Final Score: " + finalScore;
		s[2] = "Press 'R' to restart game.";
	}

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 3; i++) {
    	glRasterPos2i(350, ((-i * 20) - 70));
  		drawTextTitles(s[i]);
  	}
}
/* Controls Level Lost state */
void UserInterface::levelLost(){

	char buf1[5];
	double temp1 = Interactivity::getLives();
	snprintf(buf1, sizeof(buf1), "%f", temp1);
	string lifeTotal(buf1);

	string s[3];
	s[0] = "You Died";
	s[1] = "Current Lives: " + lifeTotal;
	s[2] = "Press 'R' to restart level.";

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 3; i++) {
    	glRasterPos2i(350, ((-i * 20) - 70));
  		drawTextTitles(s[i]);
  	}
}
/* Draws left test UI */
void drawLeft() {
	char buf1[5];
	char buf2[5];
	char buf3[5];
	char buf4[5];
	char buf5[5];
	char buf6[5];

	UserInterface::readHighScore(); // Reads in high score from text file

	double temp1 = Interactivity::getLevel();
	double temp2 = (Interactivity::getAmountOfBlocks() - Interactivity::getBeenTo());
	double temp3 = UserInterface::getScore();
	double temp4 = UserInterface::getTime();
	double temp5 = Interactivity::getLives();
	double temp6 = highScore;

	snprintf(buf1, sizeof(buf1), "%f", temp1);
	snprintf(buf2, sizeof(buf2), "%f", temp2);
	snprintf(buf3, sizeof(buf3), "%f", temp3);
	snprintf(buf4, sizeof(buf4), "%f", temp4);
	snprintf(buf5, sizeof(buf5), "%f", temp5);
	snprintf(buf6, sizeof(buf6), "%f", temp6);

	string level(buf1);						// char array to float
	string blocksLeft(buf2);				// char array to float
	string scoreTot(buf3);					// char array to float
	string currTime(buf4);					// char array to float
	string currLives(buf5);					// char array to float
	string hScore(buf6);					// char array to float

	string s[5];
    s[0] = "Current Level: " + level;
    s[1] = "Blocks Left: " + blocksLeft;
    s[2] = "Score: " + scoreTot;
    s[3] = "Time Left: " + currTime + " s";
    s[4] = "Lives Left: " + currLives;

    string use = "High Score: " + hScore;

	// Render each string
	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 5; i++) {
    	glRasterPos2i(10, ((-i * 20) + 30));
  		drawText(s[i]);
 	}
    glRasterPos2i(375, 30);
    drawHighScore(use); //Draws highscore to screen
}
/* Draws minimap on top right of UI */
void drawRight() {
	glPushMatrix();
	glTranslatef(0, -490, 0);
	glRasterPos2i(0, 0);

	glDisable(GL_LIGHTING);
	glColor3f(0, 0.509, 0.501);
	glBegin(GL_QUADS);
		glVertex2f(760.0, 340.0);
		glVertex2f(760.0, 540.0);
		glVertex2f(960.0, 540.0);
		glVertex2f(960.0, 340.0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		glVertex2f(750.0, 330.0);
		glVertex2f(750.0, 540.0);
		glVertex2f(960.0, 540.0);
		glVertex2f(960.0, 330.0);
	glEnd();
	
	switch(Interactivity::getLevel()) {
		case 1:
			glTranslatef(905, 485, 0);
			glScalef(20, 20, 1);
			glRotatef(90, 1, 0, 0);
			glRotatef(270, 0, 1, 0);
			break;
		case 2:
			glTranslatef(925, 495, 0);
			glScalef(15, 15, 1);
			glRotatef(90, 1, 0, 0);
			glRotatef(270, 0, 1, 0);
			break;
		case 3:
			glTranslatef(935, 510, 0);
			glScalef(12, 12, 1);
			glRotatef(90, 1, 0, 0);
			glRotatef(270, 0, 1, 0);
			break;
	}

	Environment::drawBoard();	
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
/* Draws the intro screen */
void drawIntro(){

	string s[10];
	s[0] = "Welcome to Q*bert!";
	s[1] = "Here are the rules:";
	s[2] = "-Controls are found in terminal.";
	s[3] = "-By stepping on a block for the first time it will change colour, and you'll gain 1;";
	s[4] = "-If you step on a block that has already been stepped on, you lose 1 point;";
	s[5] = "-You lose a life by jumping off the ledge, or touching an enemy, resulting in -15 points;";
	s[6] = "-A Game Over occurs when either yourun out of lives or run out of time;";
	s[7] = "-Whatever time you have left upon level completion will be added to your score;";
	s[8] = " ";
	s[9] = "Press 'R' to continue to start!";

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 10; i++) {
    	glRasterPos2i(10, ((-i * 20) + 30));
  		drawText2(s[i]);
  	}
}

// draws the player and calls the necessary logic functions
void UserInterface::drawUI() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
		glLoadIdentity();
		gluOrtho2D(0, 960, 50 - 540, 50);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glDisable(GL_CULL_FACE);

			glClear(GL_DEPTH_BUFFER_BIT);
			glColor3f(0, 0, 0);


			if(UserInterface::getIntroState()){
				drawIntro();
				//UserInterface::setIntroState();
			}

			else{
				drawLeft();
				drawRight();

				if(UserInterface::getWinGameState())
					UserInterface::gameOver();
				
				else if(UserInterface::getGameOverState())
					UserInterface::gameOver();

				else if(UserInterface::getLevelState())
					UserInterface::levelLost();

				else if(UserInterface::getFinishedLevelState())
					UserInterface::finishedLevel();
			}
		  	// Making sure we can render 3D again
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}