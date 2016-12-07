#ifndef ENEMY_H
#define ENEMY_H

#include "Structure.h"

class Enemy {
bool enemyMoved;					// To add the initial spot

int ID;								// The enemy's ID
int enemyRot;						// The rotation angle

float enemyDisp[4];					// The transformation matrix

public:
	void init(int id);				// "constructor"
	Structure::point3D getCoor();	// Get x, y, z of where the enemy is
	void setRotation(int change);	// Set the rotation of the enemy
	void drawEnemy(bool step);		// Draw the enemy
private:
	void draw();					// draw the model
};

#endif