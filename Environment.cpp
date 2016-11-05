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

float Environment::block[8][3] = {{-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1},
                                  {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}};

void Environment::drawBlock(int a, int b, int c, int d) {
	glColor3ub(175, 180, 43);
	glBegin(GL_POLYGON);
		glVertex3fv(block[a]);
		glVertex3fv(block[b]);
		glVertex3fv(block[c]);
		glVertex3fv(block[d]);
	glEnd();
}

void Environment::drawBlocks() {
	drawBlock(0, 3, 2, 1);
	drawBlock(1, 0, 4, 5);
	drawBlock(5, 1, 2, 6);
	drawBlock(2, 3, 7, 6);	
	drawBlock(6, 5, 4, 7);
	drawBlock(4, 0, 3, 7);
}

void Environment::drawEnvironment() {
	drawBlocks();
	//water
}
