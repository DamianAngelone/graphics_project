//opengl cross platform includes
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
#include <ctime>

using namespace std;

// Include project files
#include "Interactivity.h"

const int WIDTH = 960;
const int HEIGHT = 540;

bool fast = true;
bool startupFix = false; // stops the second tick from happening to fast
bool pause = false;

void display(void) {
	glClearColor(95.0/255, 195.0/255, 240.0/255, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void Redraw(int i) {
	if (!pause) {
		if (startupFix) {
			glutPostRedisplay();
		}
		startupFix = true;
		glutTimerFunc(17, Redraw, 0);
	}
}

void init() {
	glutDisplayFunc(display);
	glutKeyboardFunc(Interactivity::keyboard);
	glutSpecialFunc(interactivity::special);
	// Graphics start
	Redraw(0);
}

int main(int argc, char** argv) {
	Interactivity::printInstructions();
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Conway");
	init();
	glutMainLoop();
	return(0);
}