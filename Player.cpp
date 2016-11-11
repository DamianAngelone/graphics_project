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
int Player::x = 0.0;					// x position of the player
int Player::y = 0.0;					// y position of the player
int Player::z = 0.0;					// z position of the player
int rot = 270;							// The rotation angle

float translate[] = {0.0, 1.5, 0.0};	// The transformation matrix

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

void Player::drawPlayer(bool step) {
	if (step) {			// Rotate based off keyboard
		switch(rot) {
			case 0:		// Left
				translate[0] += JUMPSIZE;
				translate[1] -= JUMPSIZE;
				break;
			case 90:	// Backwards
				translate[1] -= JUMPSIZE;
				translate[2] -= JUMPSIZE;
				break;
			case 180:	// Right
				translate[0] -= JUMPSIZE;
				translate[1] += JUMPSIZE;
				break;
			case 270:	// Forwards
				translate[1] += JUMPSIZE;
				translate[2] += JUMPSIZE;
				break;
		}
	}
	glPushMatrix();
		glTranslatef(translate[0], translate[1], translate[2]);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0, 0, 0); 
		glutSolidTeapot(0.5);
	glPopMatrix();
}