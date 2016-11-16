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

unsigned char colours[6][4] = {{244, 67,  54, 1},		// Red
		                   	   {33,  150, 243,1 },		// Blue
		                   	   {0,   150, 36, 1},		// Teal
		                   	   {1,   193, 7, 1},		// Amber
		                   	   {158, 158, 158, 1},		// Gray
		                       {205, 220, 57, 1}};		// Lime
		                       
int blocks[3] = {3, 5, 8};		// Number of blocks in a row for each level

// Get the number of blocks in a row
int Environment::getLength() {
	return blocks[Interactivity::getLevel() - 1];
}

void drawBoard(){

	int len = blocks[Interactivity::getLevel() - 1];
	int max = sizeof(colours)/sizeof(colours[0]) - 1, 
		colour = max;
	for (int i=0; i<len; ++i) {
		for (int j=0; j<len - i; ++j) {

			float amb2[] = {colours[colour][0]/150, colours[colour][1]/150, colours[colour][2]/150, 1}; 
			glMaterialfv(GL_FRONT, GL_AMBIENT, amb2);
			glPushMatrix();


				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glutSolidCube(2);

				// Draw column
				for (int k=-8; k<j * 2; k+=2) {
					glTranslatef(0, -2, 0);
					glutSolidCube(2);
				}
				--colour;
				if (colour == -1)
					colour = max;
			glPopMatrix();
		}
	}
}

void drawWater(){

	int len = 2*(Environment::getLength() + 4);
	//material to make water plane look like water.
	float m_ambient[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	float m_diff[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
	float m_specular[] = {0, 0.501, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	float m_shiny = 0.25f;
	glMaterialf(GL_FRONT, GL_SHININESS, m_shiny);


	//draws the water plane.
	for(int i = -8; i < len; i++){
		for(int j = -8; j < len; j++){

			glBegin(GL_QUAD_STRIP);
			glVertex3f(i    , -0.25, j + 1);
			glVertex3f(i + 1, -0.25, j + 1);
			glVertex3f(i    , -0.25, j    );
			glVertex3f(i + 1, -0.25, j    );
			glEnd();	
		}
	}
}

void drawSand(){

	int len = 2*(Environment::getLength() + 4);

	float amb[] = {0.806, 0.567, 0.48, 1};
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	float diff2[] = {0.806, 0.567, 0.48, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff2);
	float spec[] = {0.806, 0.567, 0.48, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);

	//draws the sand plane.
	for(int i = -8; i < len; i++){
		for(int j = -8; j < len; j++){

			glBegin(GL_QUAD_STRIP);
			glVertex3f(i    , -8.1, j + 1);
			glVertex3f(i + 1, -8.1, j + 1);
			glVertex3f(i    , -8.1, j    );
			glVertex3f(i + 1, -8.1, j    );
			glEnd();	
		}
	}

}


// Draws everything except the player/enemies
void Environment::drawEnvironment() {
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawBoard();
	drawSand();
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(2.0f, 1.0f);
	drawWater();
	//glDisable(GL_POLYGON_OFFSET_FILL);
}