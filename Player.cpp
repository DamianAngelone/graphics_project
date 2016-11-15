#include "Player.h"
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
using namespace std;

// Include project files
#include "Environment.h"

const int JUMPSIZE = 2;
int Player::x = 0.0;						// x position of the player
int Player::y = 0.0;						// y position of the player
int Player::z = 0.0;						// z position of the player
int rot = 270;								// The rotation angle

float displacement[] = {0.0, 1.5, 0.0};		// The transformation matrix
float velocity[] = {0.0, 0.0, 0.0};			// The velocity matrix
float acceleration[] = {0.0, -0.1, 0.0};	// The velocity matrix

Player::point3D Player::getCoor() {
	point3D position;
	position.x = x;
	position.y = y;
	position.z = z;
	return position;
}

void Player::setRotation(int change) {
	rot = change;
}

void physics() {
	velocity[0] = acceleration[0] + velocity[0];
	velocity[1] = acceleration[1] + velocity[1];
	cout << velocity[1] << endl;
	velocity[2] = acceleration[2] + velocity[2];
}

void Player::drawPlayer(bool step) {
	physics();
	if (step) {			// Rotate based off keyboard
		switch(rot) {
			case 0:		// Left
				displacement[0] += JUMPSIZE;
				displacement[1] -= JUMPSIZE;
				break;
			case 90:	// Backwards
				displacement[1] -= JUMPSIZE;
				displacement[2] -= JUMPSIZE;
				break;
			case 180:	// Right
				displacement[0] -= JUMPSIZE;
				displacement[1] += JUMPSIZE;
				break;
			case 270:	// Forwards
				displacement[1] += JUMPSIZE;
				displacement[2] += JUMPSIZE;
				break;
		}
	}
	glPushMatrix();
		glTranslatef(displacement[0] + velocity[0], 
			         displacement[1] + velocity[1],
			         displacement[2] + velocity[2]);
		glRotatef(rot, 0, 1, 0);
		glutSolidTeapot(0.5);
	glPopMatrix();
}