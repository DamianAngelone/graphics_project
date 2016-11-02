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

const int WIDTH = 700;
const int HEIGHT = 700;

bool fast = true;
bool startupFix = false; // stops the second tick from happening to fast
bool pause = false;

void display(void) {
	glClearColor(230.0/255, 230.0/255, 230.0/255, 0);
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

void mouse(int btn, int state, int x, int y) {
	x = (x - 15) / 13.4;
	y = -1 * (y - 685) / 13.4;
}

void keyboard(unsigned char key, int xIn, int yIn) {
	switch (key) {
		case 'q':
		case 'Q':
		case 27:
			exit(0);
			break;
	}
}

void printInstructions() {
	cout << "INSTRUCITONS: " << endl;
}

int main(int argc, char** argv) {
	printInstructions();
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Conway");
	// Interactivity
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	// Graphics start
	Redraw(0);
	glutMainLoop();

	return(0);
}