#include "Environment.h"
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

#include <iostream>
using namespace std;

// Include project files
#include "Interactivity.h"

unsigned char colours[6][3] = {{244, 67,  54},		// Red
		                   	   {33,  150, 243},		// Blue
		                   	   {0,   150, 36},		// Teal
		                   	   {1,   193, 7},		// Amber
		                   	   {158, 158, 158},		// Gray
		                       {205, 220, 57}};		// Lime
		                       
int blocks[3] = {3, 5, 9};		// Number of blocks in a row for each level

// Get the number of blocks in a row
int Environment::getLength() {
	return blocks[Interactivity::getLevel() - 1];
}

void drawWater(){

	int len = 2*(Interactivity::getLevel() + 3);
	
	float diffuse[] = {0,0.1,2,0.5};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	for(int i = -4; i < len; i++){
		for(int j = -4; j < len; j++){

			glBegin(GL_QUAD_STRIP);
			glVertex3f(i    , -0.5, j + 1);
			glVertex3f(i + 1, -0.5, j + 1);
			glVertex3f(i    , -0.5, j    );
			glVertex3f(i + 1, -0.5, j    );
			glEnd();	
		}
	}
}

// Draws everything except the player/enemies
void Environment::drawEnvironment() {
	int len = blocks[Interactivity::getLevel() - 1];
	int max = sizeof(colours)/sizeof(colours[0]) - 1,
	    colour = max;
	for (int i=0; i<len; i++) {
		for (int j=0; j<len - i; j++) {
			glPushMatrix();
				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glColor3ubv(colours[colour]);
				glutSolidCube(2);
				--colour;
				if (colour == -1)
					colour = max;
			glPopMatrix();
		}
	}
	drawWater();
}