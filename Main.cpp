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

bool startupFix = false;	 	// stops the second tick from happening to fast
bool pause = false;				// if the game is paused

float eye[] = {-5, -5, -5};		// The first 3 paramters of gluLookAt
float center[] = {0, 0, 0};		// The 4-6 parameters of gluLookAt

void display(void) {
	glClearColor(95.0/255, 195.0/255, 240.0/255, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	glColor3f(1, 0, 0);
	glutSolidTeapot(1);
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
	glutSpecialFunc(Interactivity::special);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, 1, 1, 400);

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