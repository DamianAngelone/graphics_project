#include "Enemy.h"
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

#include <cmath>
#include <iostream>
using namespace std;

// Include project files
#include "Environment.h"
#include "Interactivity.h"

const int JUMPSIZE = 2;

void Enemy::init(int id) {
	ID = id;
	rotate = 180;
	enemyMoved = false;
	switch(ID) {
		case 0:
			enemyDisp[0] = 8;
			enemyDisp[1] = 1.5;
			enemyDisp[2] = 8;
			break;
		case 1:
			enemyDisp[0] = 0;
			enemyDisp[1] = ((Interactivity::getLength() - 1) * 2) + 1.5;
			enemyDisp[2] = Interactivity::getLength() * 2;
			break;
		case 2:
			enemyDisp[0] = 6;
			enemyDisp[1] = 1.5;
			enemyDisp[2] = 6;
			break;
	}
}

// Get x, y, z of where the enemy is
Structure::point3D Enemy::getCoor() {
	Structure::point3D position;
	position.x = enemyDisp[0];
	position.y = enemyDisp[1];
	position.z = enemyDisp[2];
	return position;
}

// Change the player's orientation
void Enemy::setRotation(int change) {
	rotate = change;
}

bool inBounds(int x, int z) {
	int len = Interactivity::getLength() * 2;
	return x > -1 &&
		   z > -1 &&
		   x < len &&		// further edge
		   z < len &&		// further edge
		   x != z + 2;  	// dont count inside jump out of bounds
}

// draws the player and calls the necessary logic functions
void Enemy::drawEnemy(bool step) {
	if (step) {	// Move the player
		int rotate;
		bool findRotate = false;
		while (!findRotate) {
			rotate = rand() % 4;
			switch(rotate) {
				case 0:		// Left
					if (inBounds(enemyDisp[0] + JUMPSIZE, enemyDisp[2]))
						findRotate = true;
					break;
				case 1:	// Backwards
					if (inBounds(enemyDisp[0], enemyDisp[2] - JUMPSIZE))
						findRotate = true;
					break;
				case 2:	// Right
					if (inBounds(enemyDisp[0] - JUMPSIZE, enemyDisp[2]))
						findRotate = true;
					break;
				case 3:	// Forwards
					if (inBounds(enemyDisp[0], enemyDisp[2] + JUMPSIZE))
						findRotate = true;
					break;
			}
		}
		// Move the player based on the orientation
		switch(rotate) {
			case 0:		// Left
				enemyDisp[0] += JUMPSIZE;
				enemyDisp[1] -= JUMPSIZE;
				break;
			case 1:	// Backwards
				enemyDisp[1] -= JUMPSIZE;
				enemyDisp[2] -= JUMPSIZE;
				break;
			case 2:	// Right
				enemyDisp[0] -= JUMPSIZE;
				enemyDisp[1] += JUMPSIZE;
				break;
			case 3:	// Forwards
				enemyDisp[1] += JUMPSIZE;
				enemyDisp[2] += JUMPSIZE;
				break;
		}
		// record the new position
		//Interactivity::pushPosition(enemyDisp[0], enemyDisp[2]);
	}
	glPushMatrix();
		glTranslatef(enemyDisp[0], 
			         enemyDisp[1],
			         enemyDisp[2]);
		glRotatef(rotate, 0, 1, 0);
		glutSolidTeapot(1);
	glPopMatrix();
}