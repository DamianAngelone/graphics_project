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
#include "Interactivity.h"

bool canPhysics = false;					// If the player should enter freefall

const int JUMPSIZE = 2;
int rot = 270;								// The rotation angle

float displacement[] = {0.0, 1.5, 0.0};		// The transformation matrix
float velocity[] = {0.0, 0.0, 0.0};			// The velocity matrix
float acceleration[] = {0.0, 0.0, 0.0};		// The velocity matrix

Player::point3D Player::getCoor() {
	point3D position;
	position.x = displacement[0];
	position.y = displacement[1];
	position.z = displacement[2];
	return position;
}

// Change the player's orientation
void Player::setRotation(int change) {
	rot = change;
}

// Computes the velocities from the acceleration
void physics() {
	velocity[0] = acceleration[0] + velocity[0];
	velocity[1] = acceleration[1] + velocity[1];
	velocity[2] = acceleration[2] + velocity[2];
}

// Checks if the player is on a block
void offBlock() {
	if (displacement[0] > Environment::getLength() + 1 ||	// far edges
		displacement[2] > Environment::getLength() + 1 ||
		displacement[0] < 0 || displacement[2] < 0 ||		// close edges
		// going left/down "into" the board with no block
		displacement[0] == displacement[2] + 2) {
		canPhysics = true;
		acceleration[1] = -0.2;
		switch (rot) {
			case 0:		// Left
				acceleration[0] = 0.08;
				break;
			case 90:	// Backwards
				acceleration[2] = -0.08;
				break;
			case 180:	// Right
				acceleration[0] = -0.08;
				break;
			case 270:	// Forwards
				acceleration[2] = 0.08;
				break;
		}
	}
}

// draws the player and calls the necessary logic functions
void Player::drawPlayer(bool step) {
	// If the player is not on a block, do physics
	if (!canPhysics)
		offBlock();
	if (canPhysics)		// not else because offBlock changes canPhysics
		physics();
	if (step && !canPhysics) {	// Rotate based off keyboard
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