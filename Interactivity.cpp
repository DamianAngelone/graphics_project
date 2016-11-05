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
			--eye[0];
			--center[0];
			++eye[2];
			++center[2];
 			break;
 		case GLUT_KEY_RIGHT:
			++eye[0];
			++center[0];
			--eye[2];
			--center[2];
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