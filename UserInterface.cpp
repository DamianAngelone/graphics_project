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

			char buf1[5];
			char buf2[5];
			char buf3[5];
			char buf4[5];

			double temp1 = Interactivity::getLevel();
			double temp2 = (Interactivity::getAmountOfBlocks() - Interactivity::getBeenTo());
			double temp3 = UserInterface::getScore();
			double temp4 = UserInterface::getTime();

			snprintf(buf1, sizeof(buf1), "%f", temp1);
			snprintf(buf2, sizeof(buf2), "%f", temp2);
			snprintf(buf3, sizeof(buf3), "%f", temp3);
			snprintf(buf4, sizeof(buf4), "%f", temp4);

			string level(buf1);						// char array to float
			string blocksLeft(buf2);				// char array to float
			string scoreTot(buf3);					// char array to float
			string currTime(buf4);					// char array to float

			//cout << "level: " << temp1 << " blocks left: " << temp2 << " score: " << temp3;

			string s[4];
		    s[0] = "Current Level: " + level;
		    s[1] = "Blocks Left: " + blocksLeft;
		    s[2] = "Score: " + scoreTot;
		    s[3] = "Time Left: " + currTime;

			// Render each string
			int v = sizeof(s)/24; // number of strings to draw
		    for(int i = 0; i < 4; i++) {
		    	glRasterPos2i(30, ((-i * 20) + 30));
		  		drawText(s[i]);
		 	}

		  	// Making sure we can render 3D again
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}