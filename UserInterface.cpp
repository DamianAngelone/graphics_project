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

int score = 0;
int gTime = 50;
bool gameOverState = false;					//game lost
bool gameLevelState = false;				//level lost
bool finishedLevelState = false;			//level won
bool safeToDecreaseTime = false;

void UserInterface::incrScore(){
	score += 1;
}

void UserInterface::decrScore(int n){
	if ((score - n) >= 0)
		score -= n;
	else
		score = 0;
}

int UserInterface::getScore(){

	return score;
}

void UserInterface::decrTime(){

	if (gTime > 0)
		gTime -= 1;
}

int UserInterface::getTime(){
	return gTime;
}

void UserInterface::setTime(){
	gTime = 50;
}

bool UserInterface::getGameOverState(){
	return gameOverState;
}

void UserInterface::setGameOverState(){
	gameOverState = !gameOverState;
}

bool UserInterface::getFinishedLevelState(){
	return finishedLevelState;
}

void UserInterface::setFinishedLevelState(){
	finishedLevelState = !finishedLevelState;
}

bool UserInterface::getLevelState(){
	return gameLevelState;
}

void UserInterface::setLevelState(){
	gameLevelState = !gameLevelState;
}

bool UserInterface::calculatingScore(){
	return safeToDecreaseTime;
}

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

void calculateScore(){

	usleep(5000);
	UserInterface::setCalculatingScore(true);
	UserInterface::decrTime();
	UserInterface::incrScore();
}

void UserInterface::finishedLevel(){
  	
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
	s[0] = "Level " + currLevel + " completed!";
	s[1] = "Current Score: " + currScore;
	s[2] = "Current Lives: " + currLives;
	s[3] = "Press 'R' to continue to next level.";

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 4; i++) {
    	glRasterPos2i(400, ((-i * 20) - 70));
  		drawTextTitles(s[i]);
  	}
}

void UserInterface::gameOver(){

	char buf1[5];
	double temp1 = UserInterface::getScore();
	snprintf(buf1, sizeof(buf1), "%f", temp1);
	string finalScore(buf1);

	string s[3];
	s[0] = "Game Over";
	s[1] = "Final Score: " + finalScore;
	s[2] = "Press 'R' to restart game.";

	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 3; i++) {
    	glRasterPos2i(400, ((-i * 20) - 70));
  		drawTextTitles(s[i]);
  	}
}

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
    	glRasterPos2i(390, ((-i * 20) - 80));
  		drawTextTitles(s[i]);
  	}
}

void drawLeft() {
	char buf1[5];
	char buf2[5];
	char buf3[5];
	char buf4[5];
	char buf5[5];

	double temp1 = Interactivity::getLevel();
	double temp2 = (Interactivity::getAmountOfBlocks() - Interactivity::getBeenTo());
	double temp3 = UserInterface::getScore();
	double temp4 = UserInterface::getTime();
	double temp5 = Interactivity::getLives();

	snprintf(buf1, sizeof(buf1), "%f", temp1);
	snprintf(buf2, sizeof(buf2), "%f", temp2);
	snprintf(buf3, sizeof(buf3), "%f", temp3);
	snprintf(buf4, sizeof(buf4), "%f", temp4);
	snprintf(buf5, sizeof(buf5), "%f", temp5);

	string level(buf1);						// char array to float
	string blocksLeft(buf2);				// char array to float
	string scoreTot(buf3);					// char array to float
	string currTime(buf4);					// char array to float
	string currLives(buf5);					// char array to float

	string s[5];
    s[0] = "Current Level: " + level;
    s[1] = "Blocks Left: " + blocksLeft;
    s[2] = "Score: " + scoreTot;
    s[3] = "Time Left: " + currTime + " s";
    s[4] = "Lives Left: " + currLives;

	// Render each string
	int v = sizeof(s)/24; // number of strings to draw
    for(int i = 0; i < 5; i++) {
    	glRasterPos2i(10, ((-i * 20) + 30));
  		drawText(s[i]);
 	}
}

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

			drawLeft();
			drawRight();

			if(UserInterface::getGameOverState())
				UserInterface::gameOver();

			else if(UserInterface::getLevelState())
				UserInterface::levelLost();

			else if(UserInterface::getFinishedLevelState())
				UserInterface::finishedLevel();

		  	// Making sure we can render 3D again
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}