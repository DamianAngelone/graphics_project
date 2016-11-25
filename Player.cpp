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

#include <cmath>
#include <iostream>
using namespace std;

// Include project files
#include "Environment.h"
#include "Interactivity.h"

bool canPhysics = false;					// If the player should enter freefall
bool moved = false;							// To add the initial spot

const int JUMPSIZE = 2;
int rot = 270;								// The rotation angle

float displacement[] = {0.0, 1.5, 0.0};		// The transformation matrix
float velocity[] = {0.0, 0.0, 0.0};			// The velocity matrix
float acceleration[] = {0.0, 0.0, 0.0};		// The velocity matrix

float pos[] = {0, 1, 0};
float rot2[] = {0, 0, 0};
GLUquadric* qobj;

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

void Player::reset() {
	canPhysics = false;
	moved = false;
	displacement[0] = 0;
	displacement[1] = 1.5;
	displacement[2] = 0;
	velocity[0] = 0;
	velocity[1] = 0;
	velocity[2] = 0;
	acceleration[0] = 0;
	acceleration[1] = 0;
	acceleration[2] = 0;
	rot = 270;
}

void drawHalfSphere(int scaley, int scalex, GLfloat r) {
   int i, j;
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable (GL_COLOR_MATERIAL);

   GLfloat v[scalex*scaley][3];
 
   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0] = r * cos(j * 2 * M_PI/scaley) * cos(i * M_PI/(2 * scalex));
       v[i*scaley+j][1] = r * sin(i * M_PI/(2 * scalex));
       v[i*scaley+j][2] = r * sin(j * 2 * M_PI/scaley) * cos(i * M_PI/(2 * scalex));
     }
   }
 
   glBegin(GL_QUADS);
     for (i=0; i<scalex - 1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i * scaley + j]);
         glVertex3fv(v[i * scaley + (j + 1) % scaley]);
         glVertex3fv(v[(i + 1) * scaley + (j + 1) % scaley]);
         glVertex3fv(v[(i + 1) * scaley + j]);
       }
     }
   glEnd();
   glDisable (GL_COLOR_MATERIAL);
 }

void drawQubert() {
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		glTranslatef(0, 1.0, 0);
		glRotatef(-270, 0, 1, 0);
		glColor3f(1,0.5,0);
		glScalef(0.6, 0.6, 0.6);
		//draw body
		glPushMatrix();
			glutSolidSphere(1, 100, 100);
			//eyes
			glPushMatrix();
				glColor3f(1,1,1);
				glTranslatef(-0.3,0.4,0.6);
				glutSolidSphere(0.4, 100, 100);
				//pupil
				glPushMatrix();
					glColor3f(0,0,0);
					glTranslatef(0,0.1,0.25);
					glutSolidSphere(0.2,100,100);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(0.3,0.4,0.6);
			glutSolidSphere(0.4, 100, 100);
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(0,0.1,0.25);
				glutSolidSphere(0.2,100,100);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix(); //nose
			glColor3f(1,0.5,0);
			gluCylinder(qobj,0.35,0.55,2,100,100);
			glPushMatrix(); //disc
				glTranslatef(0,0,2);
				glColor3f(1,0.5,0);
				gluDisk(qobj, 0.35, 0.55,  100, 100);
			glPopMatrix();

			glColor3f(0,0,0);
			gluCylinder(qobj,0.2,0.35,2,100,100);
			glPushMatrix();
				glTranslatef(0,0,1.5);
				glColor3f(1,0.5,0);
				//glutSolidTorus(0.4,0.45,100,100);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glColor3f(1,0.5,0);
			glRotatef(90,1,0,0);
			glTranslatef(-0.3,0,0);
			gluCylinder(qobj,0.15,0.15,2,100,100);
			//left foot
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glScalef(1,1,1.5);
				glTranslatef(0,-2.2,0.15);
				drawHalfSphere(100,100,0.3);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glColor3f(1,0.5,0);
			glRotatef(90,1,0,0);
			glTranslatef(0.3,0,0);
			gluCylinder(qobj,0.15,0.15,2,100,100);
			//right foot
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glScalef(1,1,1.5);
				glTranslatef(0,-2.2,0.15);
				drawHalfSphere(100,100,0.3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();//body

	glDisable(GL_COLOR_MATERIAL);
}

// Computes the velocities from the acceleration
void physics() {
	velocity[0] = acceleration[0] + velocity[0];
	velocity[1] = acceleration[1] + velocity[1];
	velocity[2] = acceleration[2] + velocity[2];
}

// Checks if the player is on a block
void offBlock() {
	if (displacement[0] == 2 * Environment::getLength() ||	// far edges
		displacement[2] == 2 * Environment::getLength() ||
		displacement[0] < 0 || displacement[2] < 0 ||		// close edges
		// going left/down "into" the board with no block
		displacement[0] == displacement[2] + 2) {
		canPhysics = true;
		acceleration[1] = -0.2;
		switch (rot) {
			case 0:		// Left
				acceleration[0] = 0.05;
				break;
			case 90:	// Backwards
				acceleration[2] = -0.05;
				break;
			case 180:	// Right
				acceleration[0] = -0.05;
				break;
			case 270:	// Forwards
				acceleration[2] = 0.05;
				break;
		}
	}
}

// draws the player and calls the necessary logic functions
void Player::drawPlayer(bool step) {
	
	qobj = gluNewQuadric();

	if (!canPhysics)			// If the player is not on a block, do physics
		offBlock();
	if (canPhysics)				// not else because offBlock changes canPhysics
		physics();
	if (step && !canPhysics) {	// Move the player
		// Add the initial spot
		if (!moved) {
			Interactivity::pushPosition(displacement[0], displacement[2]);
			moved = true;
		}
		// Move the player based on the orientation
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
		// record the new position
		Interactivity::pushPosition(displacement[0], displacement[2]);
	}
	glPushMatrix();
		glTranslatef(displacement[0] + velocity[0], 
			         displacement[1] + velocity[1],
			         displacement[2] + velocity[2]);
		glRotatef(rot, 0, 1, 0);
		drawQubert();
		//glutSolidTeapot(0.5);
	glPopMatrix();
}