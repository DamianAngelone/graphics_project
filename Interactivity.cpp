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
#include "Environment.h"

int level = 1;						// the level the game is on
int playerBeenLength = 0;			// the level the game is on

float theta = 40;					// The angle of rotation
// float array instead of point3D because you can't initialize a struct up here
// The first 3 paramters of gluLookAt
float eye[] = {Environment::getLength(), Environment::getLength() * 3, -12};
// The 4-6 paramters of gluLookAt	
float center[] = {Environment::getLength(), 0, Environment::getLength() * 2 + 8};

Structure::point3D playerBeen[50];

int Interactivity::getLevel() {	 // Get the game level
	return level;
}

float Interactivity::getTheta() { // Get the horizontal angle of rotation
	return theta;
}

Structure::point3D Interactivity::getEye() { // Get first 3 paramters of gluLookAt
	Structure::point3D point;
	point.x = eye[0];
	point.y = eye[1];
	point.z = eye[2];
	return point;
}

Structure::point3D Interactivity::getCenter() { // Get 4-6 paramters of gluLookAt
	Structure::point3D point;
	point.x = center[0];
	point.y = center[1];
	point.z = center[2];
	return point;
}

Structure::point3D* Interactivity::getPlayerBeen() {
	return playerBeen;
}

// Move back the camera when the game progress through the levels
void cameraAdjust() {
	eye[0] = Environment::getLength();
	eye[1] = Environment::getLength() * 3;
	center[0] = Environment::getLength();
	center[2] = Environment::getLength() * 2 + 8;
}

void Interactivity::pushPosition(int x, int z) {
	Structure::point3D point;
	point.x = x;
	point.z = z;
	bool duplicate = false;
	// Check for duplicate spot
	for (int i = 0; i < playerBeenLength; ++i) {
		if (playerBeen[i].x == x
			&& playerBeen[i].z == z) {
			duplicate = true;
			break;
		}
	}
	
	int len = Environment::getLength();
	// Check if its a not a duplicate spot and doesn't go past bounds
	if (!duplicate &&	// not a duplicate
		x/2 < len &&	// further edge
		z/2 < len &&	// further edge
		x != z + 2) {	// dont count inside jump out of bounds
		playerBeen[playerBeenLength] = point;
		++playerBeenLength;
		
		int numOfBlocks = (len * (len + 1))/2;
		if (playerBeenLength == numOfBlocks) {
			++level;
			for (int i = 0; i < playerBeenLength; i++) {
				playerBeen[i].x = 0;
				playerBeen[i].z = 0;
			}
			playerBeenLength = 0;
			Player::reset();
			cameraAdjust();
		}
	}
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
		case 'h':
			++level;
			break;
	}
}

void Interactivity::special(int key, int x, int y) {
	float change;
	switch (key) {
		case GLUT_KEY_LEFT:		// Rotate left
			if (theta < 75)
				theta += 5;
			break;
 		case GLUT_KEY_RIGHT:	// Rotate right
			if (theta > -75)
				theta -= 5;
 			break;
 		case GLUT_KEY_UP:		// Move camera upwards
			if (eye[1] < 30)
				eye[1] += 2;
			break;
 		case GLUT_KEY_DOWN:		// Move camera downwards
			if (eye[1] > 6)
				eye[1] -= 2;
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