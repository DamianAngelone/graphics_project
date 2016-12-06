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
#include "UserInterface.h"

int level = 1;						// the level the game is on
int playerBeenLength = 0;			// the level the game is on
int blocks[3] = {3, 5, 7};			// Number of blocks in a row for each level
int space = 0;

float theta = 40;					// The angle of rotation
// float array instead of point3D because you can't initialize a struct up here
// The first 3 paramters of gluLookAt
float eye[] = {Interactivity::getLength(), Interactivity::getLength() * 3, -12};
// The 4-6 paramters of gluLookAt	
float center[] = {Interactivity::getLength(), 0, Interactivity::getLength() * 2 + 8};

Structure::point3D playerBeen[50];

Enemy Interactivity::enemy[3];

int Interactivity::getSpace() {	 // Get the game level
	
	return space;
}

void Interactivity::setSpace(int n) {	 // Get the game level
	
	space = n;
}

int Interactivity::getLevel() {	 // Get the game level
	
	return level;
}

int Interactivity::getLength() {	// Get the number of blocks in a row
	
	return blocks[level - 1];
}

int Interactivity::getBeenTo() {	// Get the number of blocks in a row
	
	return playerBeenLength;
}

int Interactivity::getAmountOfBlocks(){

	int len = Interactivity::getLength();
	return (len * (len + 1))/2;
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
	eye[0] = Interactivity::getLength();
	eye[1] = Interactivity::getLength() * 3;
	center[0] = Interactivity::getLength();
	center[2] = Interactivity::getLength() * 2 + 8;
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
			UserInterface::decrScore();
			break;
		}
	}
	
	int len = Interactivity::getLength();
	// Check if its a not a duplicate spot and doesn't go past bounds
	if (!duplicate &&	// not a duplicate
		x/2 < len &&	// further edge
		z/2 < len &&	// further edge
		x != z + 2) {	// dont count inside jump out of bounds
		playerBeen[playerBeenLength] = point;
		++playerBeenLength;
		
		UserInterface::incrScore();
		int numOfBlocks = Interactivity::getAmountOfBlocks();
		if (playerBeenLength == numOfBlocks) {
			++level;
			for (int i = 0; i < playerBeenLength; i++) {
				playerBeen[i].x = 0;
				playerBeen[i].z = 0;
			}
			playerBeenLength = 0;
			Player::reset();
			cameraAdjust();
			Interactivity::enemy[0].init(0);
			Interactivity::enemy[1].init(1);
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
		case 32:
			space = 1;
			cout << "SPACE";
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