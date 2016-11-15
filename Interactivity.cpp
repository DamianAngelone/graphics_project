#include "Interactivity.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

// Include project files
#include "Player.h"
int level = 3;			// the level the game is on

float Interactivity::theta = 0;			// The angle of rotation
float eye[] = {8.0, 15.0, 0.0};			// The first 3 paramters of gluLookAt
float center[] = {-6, 0.0, 0.0};		// The first 4-6 paramters of gluLookAt

// Get the game level
int Interactivity::getLevel() {
	return level;
}

Interactivity::point3D Interactivity::getEye() {
	Interactivity::point3D point;
	point.x = eye[0];
	point.y = eye[1];
	point.z = eye[2];
	return point;
}

Interactivity::point3D Interactivity::getCenter() {
	Interactivity::point3D point;
	point.x = center[0];
	point.y = center[1];
	point.z = center[2];
	return point;
}

void Interactivity::keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':	// Quit the program
		case 'Q':
		case 27:
			exit(0);
			break;
		case 'w':	// Forward
		case 'W':
			Player::setRotation(270);
			break;
		case 'a':	// Left
		case 'A':
			Player::setRotation(0);
			break;
		case 's':	// Backwards
		case 'S':
			Player::setRotation(90);
			break;
		case 'd':	// Right
		case 'D':
			Player::setRotation(180);
			break;
	}
}

void Interactivity::special(int key, int x, int y) {
	float change;
	switch (key) {
		case GLUT_KEY_LEFT:			// Rotate around the scene
 		case GLUT_KEY_RIGHT:
			change = key == GLUT_KEY_LEFT ? 1 : -1;			// postive or negative
			theta = theta < 360 ? theta + change * 5 : 0;	// increment or reset to 0
 			break;
 		case GLUT_KEY_UP:			// Move camera strictly upwards
			eye[1] += 2;
			center[1] += 2;
 			break;
 		case GLUT_KEY_DOWN:			// Move camera striclty downwards
			eye[1] -= 2;
			center[1] -= 2;
 			break;
	}
}

void Interactivity::printInstructions() {
	cout << "-----------------------------------"  << endl;
	cout << "INSTRUCITONS: " << endl;
	cout << "KEY             ACTION" << endl;
	cout << "Q               Quit"   << endl;
	cout << "ESC"            << endl;
	cout << "LEFT            Rotate camera left" << endl;
	cout << "RIGHT           Rotate camera right" << endl;
	cout << "UP              Move camera upwards" << endl;
	cout << "DOWN            Move camera downwards" << endl;
	cout << "W               Turn the character forwards" << endl;
	cout << "A               Turn the character left" << endl;
	cout << "S               Turn the character backwards" << endl;
	cout << "D               Turn the character right" << endl;
	cout << "-----------------------------------"  << endl;
}