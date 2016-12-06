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
using namespace std;

// Include project files
#include "Interactivity.h"
#include "Interactivity.h"

int score = 0;
int gTime = 200;

void UserInterface::incrScore(){

	score += 1;
}
void UserInterface::decrScore(){

	if (score > 0)
		score -= 1;
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


// draws the player and calls the necessary logic functions
void UserInterface::drawUI() {
	
	/*
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
		glLoadIdentity();
		gluOrtho2D(0, WIDTH, 50 - HEIGHT, 50);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glDisable(GL_CULL_FACE);

			glClear(GL_DEPTH_BUFFER_BIT);
			glColor3f(0, 0, 0);

			string s[3];
		    s[0] = "Current Level: " + Interactivity::getLevel();
		    s[1] = "Blocks Left: " + (Interactivity::getAmountOfBlocks() - Interactivity::getBeenTo());
		    s[2] = "Score: " + UserInterface::getScore();

			// Render each string
			int v = (selected > -1 ? sizeof(s)/24 : 2); // number of strings to draw
		    for(int i = 0; i < v; i++) {
		    	glRasterPos2i(10, ((-i * 20) + 30));
		  		drawText(s[i]);
		 	}

		  	// Making sure we can render 3D again
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	*/
}