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
#include "UserInterface.h"

bool canPhysics = false;					// If the player should enter freefall
bool moved = false;							// To add the initial spot
bool stopped = false;						// To add the initial spot
bool gameOver = false;						// If game is currently in game over state
bool currOffBlock = false;					// If the player is currently off the block

const int JUMPSIZE = 2;						// Jump displacement for the player
int rot = 270;								// The rotation angle

float displacement[] = {0.0, 1.5, 0.0};		// The transformation matrix
float velocity[] = {0.0, 0.0, 0.0};			// The velocity matrix
float acceleration[] = {0.0, 0.0, 0.0};		// The velocity matrix

GLUquadric* qobj = gluNewQuadric();			// Used for drawing character

// Parameters used to keep track of player position
Structure::point3D Player::getCoor() {
	Structure::point3D position;
	position.x = displacement[0];
	position.y = displacement[1];
	position.z = displacement[2];
	return position;
}

/* Keeps track if player is off the block (lose a life) */
bool Player::currentlyOffBlock(){

	return currOffBlock;
}

/* Change the player's orientation */
void Player::setRotation(int change) {

	rot = change;
}

/* Stops player (touching sand/enemy) */
void Player::setStopped(bool b) {
	
	stopped = b;
}

/* Reset the player's position */
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

/* Draws the half-sphere for Q*bert's feet */
void drawHalfSphere(int scaley, int scalex, GLfloat r) {
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat v[scalex*scaley][3];
 
    for (int i=0; i<scalex; ++i) {
    	for (int j=0; j<scaley; ++j) {
			v[i * scaley + j][0] = r * cos(j * 2 * M_PI/scaley) * cos(i * M_PI/(2 * scalex));
			v[i * scaley + j][1] = r * sin(i * M_PI/(2 * scalex));
			v[i * scaley + j][2] = r * sin(j * 2 * M_PI/scaley) * cos(i * M_PI/(2 * scalex));
     	}
    }
	glBegin(GL_QUADS);
		for (int i=0; i<scalex - 1; ++i) {
	    	for (int j=0; j<scaley; ++j) {
		   	 	glVertex3fv(v[i * scaley + j]);
		   		glVertex3fv(v[i * scaley + (j + 1) % scaley]);
		    	glVertex3fv(v[(i + 1) * scaley + (j + 1) % scaley]);
		    	glVertex3fv(v[(i + 1) * scaley + j]);
	    	}
		}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}

/* Draws Q*bert to the scene */
void drawQubert() {
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
		glTranslatef(0, 1, 0);
		glRotatef(-270, 0, 1, 0);
		glColor3ub(244, 67, 54);
		glScalef(0.6, 0.6, 0.6);
		// Draw body
		glPushMatrix();
			glutSolidSphere(1, 100, 100);
			// Right eye
			glPushMatrix();
				glColor3f(1, 1, 1);
				glTranslatef(-0.3,0.4,0.6);
				glutSolidSphere(0.4, 100, 100);
				// Right pupil
				glPushMatrix();
					glColor3f(0, 0, 0);
					glTranslatef(0, 0.1, 0.25);
					glutSolidSphere(0.2, 100, 100);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		// Left eye
		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(0.3, 0.4, 0.6);
			glutSolidSphere(0.4, 100, 100);
			// Left pupil
			glPushMatrix();
				glColor3f(0, 0, 0);
				glTranslatef(0, 0.1, 0.25);
				glutSolidSphere(0.2, 100, 100);
			glPopMatrix();
		glPopMatrix();
		// Nose
		glDisable(GL_CULL_FACE);
		glPushMatrix();
			glColor3ub(244, 67, 54);
			gluCylinder(qobj, 0.35, 0.55, 2, 100, 100);
			glPushMatrix(); //disc
				glTranslatef(0, 0, 2);
				glColor3ub(244, 67, 54);
				gluDisk(qobj, 0.35, 0.55, 100, 100);
			glPopMatrix();
			glColor3f(0, 0, 0);
			gluCylinder(qobj, 0.2, 0.35, 2, 100, 100);
		glPopMatrix();
		glEnable(GL_CULL_FACE);
		// Left leg
		glPushMatrix();
			glColor3ub(244, 67, 54);
			glRotatef(90, 1, 0, 0);
			glTranslatef(-0.3, 0, 0);
			gluCylinder(qobj, 0.15, 0.15, 2, 100, 100);
			// Left foot
			glPushMatrix();
				glColor3ub(244, 67, 54);
				glRotatef(-90, 1, 0, 0);
				glScalef(1, 1, 3);
				glTranslatef(0, -2.2, 0.1);
				glutSolidCube(0.3);
			glPopMatrix();
		glPopMatrix();
		// Right leg
		glPushMatrix();
			glColor3ub(244, 67, 54);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0.3, 0, 0);
			gluCylinder(qobj, 0.15, 0.15, 2, 100, 100);
			// Right foot
			glPushMatrix();
				glColor3ub(244, 67, 54);
				glRotatef(-90, 1, 0, 0);
				glScalef(1, 1, 3);
				glTranslatef(0, -2.2, 0.1);
				glutSolidCube(0.3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

/* Computes the velocities from the acceleration */
void physics() {
	int x, z;
	x = floor(displacement[0] + velocity[0] + 0.5);
	z = floor(displacement[2] + velocity[2] + 0.5);
 	// Checks to see if it has touched the sand 
	// Checks if game over, or if only a single life was lost
	if (displacement[1] + velocity[1] < -9) {
		stopped = true;
		Interactivity::setLives(-1);
		// If the player runs out of lives
		if(Interactivity::getLives() == 0)
			UserInterface::setGameOverState(); // Game over
		//Or..
		else
			UserInterface::setLevelState(); // Level Lost
	} 
	// Used for when the user falls of the stage
	else {
		velocity[0] = acceleration[0] + velocity[0];
		velocity[1] = acceleration[1] + velocity[1];
		velocity[2] = acceleration[2] + velocity[2];
	}
 }

/* Checks if the player is on a block */
void offBlock() {
	currOffBlock = false;
	// Checks if the suer is not on a block
	if (displacement[0] == 2 * Interactivity::getLength() ||	// Far edges
		displacement[2] == 2 * Interactivity::getLength() ||
		displacement[0] < 0 || displacement[2] < 0 ||			// Close edges
		displacement[0] == displacement[2] + 2) {				// going left/down "into" the board with no block
		// Variable used for layer falling
		currOffBlock = true; 
		canPhysics = true;
		// Player is falling
		acceleration[1] = -0.35;
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

/* Draws the player and calls the necessary logic functions */
void Player::drawPlayer(bool step) {
	// If the player is stopped (touched sand or enemy)
	if (!stopped && !UserInterface::getFinishedLevelState()) {
		if (!canPhysics)			// Check if the player is on a block
			offBlock();
		if (canPhysics)				// We don't 'else' because offBlock changes canPhysics
			physics();				// If the player is not on a block, run physics
		if (Interactivity::getSpace() == 1 && !canPhysics) {	// Move the player
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
			// User can press 'space' again
			Interactivity::setSpace(0);
			// record the new position
			Interactivity::pushPosition(displacement[0], displacement[2]);
		}
	}
	glPushMatrix();
		glTranslatef(displacement[0] + velocity[0], 
			         displacement[1] + velocity[1],
			         displacement[2] + velocity[2]);
		glRotatef(rot, 0, 1, 0);
		drawQubert();
	glPopMatrix();
}