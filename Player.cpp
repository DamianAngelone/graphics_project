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

int x = 0;		// x positon of the player
int y = 0;		// y positon of the player
int z = 0;		// z positon of the player

Player::point3D Player::getCoor() {
	point3D position;
	position.x = x;
	position.y = y;
	position.z = z;
	return position;
}

void Player::drawPlayer() {
	glColor3f(1, 0, 0); 
	glutSolidTeapot(1);
}