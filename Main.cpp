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
#include "Environment.h"

const int WIDTH = 960;
const int HEIGHT = 540;

bool pause = false;		// if the game is paused

int level = 1;			// the level the game is on
int step = 0;			// When to make the game step

void display(void) {
	glClearColor(95.0/255, 195.0/255, 240.0/255, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	Interactivity::point3D eye = Interactivity::getEye();
	Interactivity::point3D center = Interactivity::getCenter();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0, 1, 0);
	glShadeModel(GL_FLAT);
	glPushMatrix();
		// Rotation of the camera affects the whole game world
		glRotatef(Interactivity::theta, 0, 1, 0);
		Environment::drawEnvironment(level);
		Player::drawPlayer(step > 1500);
	glPopMatrix();
	if (step > 1500) step = 0;
	glutSwapBuffers();
}

// Constantly redraw the screen every 17 ms for 60 fps
void redraw(int i) {
	if (!pause) {
		glutPostRedisplay();
		step += 17;
		glutTimerFunc(17, redraw, 0);
	}
}

void init() {
	// No transparency
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	// Callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(Interactivity::keyboard);
	glutSpecialFunc(Interactivity::special);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, 1, 1, 400);
	srand(time(0));
	redraw(0);
}

int main(int argc, char** argv) {
	Interactivity::printInstructions();
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Project");
	init();
	glutMainLoop();
	return(0);
}