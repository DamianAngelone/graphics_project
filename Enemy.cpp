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

GLUquadric* qObj = gluNewQuadric();

void Enemy::init(int id) {
	ID = id;
	enemyRot = 2;
	enemyMoved = false;
	// set the position based on the ID
	switch(ID) {
		case 0:
			enemyDisp[0] = 8;
			enemyDisp[1] = 1.5;
			enemyDisp[2] = 8;
			break;
		case 1:
			enemyDisp[0] = 0;
			enemyDisp[1] = (Interactivity::getLength() * 2) + 1.5;
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
	enemyRot = change;
}

// Checks if the next step is on a block still.
bool inBounds(int x, int z) {
	int len = Interactivity::getLength() * 2;
	return x > -1 &&
		   z > -1 &&
		   x < len &&		// further edge
		   z < len &&		// further edge
		   x != z + 2;  	// dont count inside jump out of bounds
}

// Draw the model of the players
void Enemy::draw() {
	float origin[3] = {0, 0, 0};
	glPushMatrix();
		glScalef(0.7, 0.7, 0.7);
		glTranslatef(0, 1, 0);
		// Rotate the body to the correct orientation
		switch (enemyRot) {
			case 0:
				glRotatef(90, 0, 1, 0);
				break;
			case 1:
				glRotatef(180, 0, 1, 0);
				break;
			case 2:
				glRotatef(270, 0, 1, 0);
				break;
			case 3:
				glRotatef(0, 0, 1, 0);
				break;
		}


		//draw body
		glutSolidCube(1);

		//draw buttons
		glPushMatrix();
			glTranslatef(0, 0.35, 0.5);
			glColor3f(0, 0, 0);
			glutSolidSphere(0.1, 10, 10);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0.15, 0.5);
			glColor3f(0, 0, 0);
			glutSolidSphere(0.1, 10, 10);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -0.05, 0.5);
			glColor3f(0, 0, 0);
			glutSolidSphere(0.1, 10, 10);
		glPopMatrix();

		glPushMatrix();
			//translate relative to body, and draw head
			glTranslatef(0, 1.25, 0);
			glColor3f(1,1,1);
			//gluCylinder(qObj,1,1,2,100,100);
			glutSolidSphere(0.5, 16, 16);
			
			//translate and draw right eye
			glPushMatrix();
				glTranslatef(0.2, 0.15, 0.45);
				glColor3f(0,0,0);
				glutSolidSphere(0.1, 10, 10);
			glPopMatrix();

			//translate and draw left eye
			glPushMatrix();
				glTranslatef(-0.2, 0.15, 0.45);
				glColor3f(0,0,0);
				glutSolidSphere(0.1, 10, 10);
			glPopMatrix();

			//translate and draw nose
			glPushMatrix();
				glTranslatef(0, 0, 0.5);
				glColor3f(1,0.4,0);
				glutSolidSphere(0.1, 10, 10);
			glPopMatrix();
		glPopMatrix();//Head
		
		//right arm shoulder	
		glPushMatrix();
			glTranslatef(-0.5,0.6,0);	
			glColor3f(1,0.4,0);
			glutSolidSphere(0.3, 30, 30);
			//right arm
			glPushMatrix();
				glRotatef(-90,0,1,0);
				glRotatef(45,1,0,0);	
				//glTranslatef(0,0,0);
				glColor3f(0,0,1);
				gluCylinder(qObj,0.2,0.2,0.7,100,100);
				//right hand
				glPushMatrix();
					glTranslatef(0,0,0.9);
					glColor3f(1,1,1);
					glutSolidSphere(0.3, 30, 30);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		//left arm shoulder	
		glPushMatrix();
			glTranslatef(0.5,0.6,0);	
			glColor3f(1,0.4,0);
			glutSolidSphere(0.3, 30, 30);
			//left arm
			glPushMatrix();
			//glTranslatef(0.2,0,0);
				glColor3f(0.8,0.6,0.7);
				glRotatef(90,0,1,0);
				glRotatef(45,1,0,0);
				glColor3f(0,0,1);
				gluCylinder(qObj,0.2,0.2,1,100,100);
				//left hand
				glPushMatrix();
					glTranslatef(0,0,0.9);
					glColor3f(1,1,1);
					glutSolidSphere(0.3, 30, 30);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		//leg join	
		glPushMatrix();
			glTranslatef(0.3,-1,0);	
			glColor3f(1,0.4,0);
			glutSolidSphere(0.2, 30, 30);
			//left leg
			glPushMatrix();
				glTranslatef(0,-0.1,0);
				glRotatef(90,1,0,0);
				glColor3f(0,0,1);
				gluCylinder(qObj,0.15,0.15,1.5,100,100);
				//left feet
				glPushMatrix();
					glTranslatef(0.1,0.15,1.5);
					glRotatef(-35,0,0,1);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();	

		//right join	
		glPushMatrix();
			glTranslatef(-0.3,-1,0);	
			glColor3f(1,0.4,0);
			glutSolidSphere(0.2, 30, 30);
			//right leg
			glPushMatrix();
				glTranslatef(0,-0.1,0);
				glRotatef(90,1,0,0);
				glColor3f(0,0,1);
				gluCylinder(qObj,0.15,0.15,1.5,100,100);
				//right feet
				glPushMatrix();
					glTranslatef(-0.1,0.15,1.5);
					glRotatef(35,0,0,1);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();	
	glPopMatrix();
}

// draws the player and calls the necessary logic functions
void Enemy::drawEnemy(bool step) {
	if (step && Interactivity::getSpace() == 0) {	// Move the player
		bool findRotate = false;
		while (!findRotate) {
			enemyRot = rand() % 4;
			switch(enemyRot) {
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
		switch(enemyRot) {
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
		glRotatef(enemyRot, 0, 1, 0);
		draw();
	glPopMatrix();
}