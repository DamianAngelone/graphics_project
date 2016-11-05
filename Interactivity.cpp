#include "Interactivity.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

#include <iostream>
using namespace std;

float rot = 0;
float Interactivity::eye[] = {-5, -5, -5};
float Interactivity::center[] = {0, 0, 0};

void Interactivity::keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':			// Quit the program
		case 'Q':
		case 27:
			exit(0);
			break;
	}
}

void Interactivity::special(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
 		case GLUT_KEY_RIGHT:
	 		r = sqrt(pow(eye[0] - center[0], 2) + pow(eye[2] - center[2], 2));
			change = key == 'GLUT_KEY_LEFT' ? 0.1 : -0.1;	// postive or negative
			rot = rot < 360 ? rot + change : 0;	// increment or reset to 0
			center[0] = r * cos(rot);					// circular motion
			center[2] = r * sin(rot);
 			break;
 		case GLUT_KEY_UP:
			++eye[1];
			++center[1];
 			break;
 		case GLUT_KEY_DOWN:
			--eye[1];
			--center[1];
 			break;
	}
}

void Interactivity::printInstructions() {
	cout << "-----------------------------------"  << endl;
	cout << "INSTRUCITONS: " << endl;
	cout << "KEY        ACTION" << endl;
	cout << "Q          Quit"   << endl;
	cout << "ESC"            << endl;
	cout << "-----------------------------------"  << endl;
}