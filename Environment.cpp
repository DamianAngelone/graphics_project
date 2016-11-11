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

unsigned char colours[6][3] = {{244, 67,  54},		// Red
		                   	   {33,  150, 243},		// Blue
		                   	   {0,   150, 36},		// Teal
		                   	   {1,   193, 7},		// Amber
		                   	   {158, 158, 158},		// Gray
		                       {205, 220, 57}};		// Lime
		                       
int blocks[3] = {3, 5, 9};		// Number of blocks for each level

void Environment::drawEnvironment(int level) {
	int len = blocks[level - 1];
	int max = sizeof(colours)/sizeof(colours[0]) - 1,
	    colour = max;
	for (int i=0; i<len; i++) {
		for (int j=0; j<len - i; j++) {
			glPushMatrix();
				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glColor3ubv(colours[colour]);
				glutSolidCube(2);
				--colour;
				if (colour == -1) colour = max;
			glPopMatrix();
		}
	}
	//water
}
