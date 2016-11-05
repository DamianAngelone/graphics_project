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
#include "Player.h"

const int WIDTH = 960;
const int HEIGHT = 540;

bool pause = false;				// if the game is paused

void display(void) {
	glClearColor(95.0/255, 195.0/255, 240.0/255, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(Interactivity::eye[0], Interactivity::eye[1], Interactivity::eye[2],
	          Interactivity::center[0], Interactivity::center[1], Interactivity::center[2], 
	          0, 1, 0);

	Player::drawPlayer();
	glFlush();
}

// Constantly redraw the screen every 17 ms for 60 fps
void Redraw(int i) {
	if (!pause) {
		glutPostRedisplay();
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