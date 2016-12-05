#include "Environment.h"
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
#include <cmath>
using namespace std;

// Include project files
#include "Interactivity.h"

bool getWaterHeight = true;
bool getSandHeight = true;

float waterHeightMap[100][100];
float sandHeightMap[100][100];

bool Environment::touchingSand(int x, float y, int z) {
	float dist = y - (sandHeightMap[x][z] - 12);
	return dist < 1 || dist < 0;
}

void createWaves(int iterations, int size) {
	//will run for how many hills was specified by the user. 
	for(int i = 0; i < iterations; i++){

		int center_X = rand() % size; 				//GRID (x) midpoint of circle (1-gridLength)                      
	    int center_Z = rand() % size;				//GRID (z) midpoint of circle (1-gridWidth)
	    float terrainCircleSize = 35; 				//random radius of circle (1-5)
	    int randomHeight = (rand() % 1) + 1;		//random height for slope (1-5)   
	    
	    //will run for every vertex in the grid.
        for(int x = 0; x < size; x++){
            for(int z = 0; z < size; z++){

				float distanceFromX = x - center_X;
                float distanceFromZ = z - center_Z;
                float totalDistance = sqrtf((distanceFromX * distanceFromX) + (distanceFromZ * distanceFromZ));
                float pd = (totalDistance * 2) / terrainCircleSize;

                if (fabs(pd) <= 1.0){
             	
                	waterHeightMap[x][z] += (randomHeight / 2.0 + cos(pd * 3.14) * randomHeight / 2.0);
                }
            }
        } 
	}
	//create normals for each plane.
	//createNormals();
}

void createSlopes(int iterations, int size) {
	//will run for how many hills was specified by the user. 
	for(int i = 0; i < iterations; i++){
		int center_X = rand() % size; 				//GRID (x) midpoint of circle (1-gridLength)                      
	    int center_Z = rand() % size;				//GRID (z) midpoint of circle (1-gridWidth)
	    float terrainCircleSize = 30; 				//random radius of circle (1-5)
	    int randomHeight = (rand() % 4) + 1;		//random height for slope (1-5)   
	    
	    //will run for every vertex in the grid.
        for(int x = 0; x < size; x++){
            for(int z = 0; z < size; z++){
				float distanceFromX = x - center_X;
                float distanceFromZ = z - center_Z;
                float totalDistance = sqrtf((distanceFromX * distanceFromX) + (distanceFromZ * distanceFromZ));
                float pd = (totalDistance * 2) / terrainCircleSize;

                if (fabs(pd) <= 1.0) {
                	sandHeightMap[x][z] += (randomHeight / 2.0 + cos(pd * 3.14) * randomHeight / 2.0);
                }
            }
        } 
	}
	//create normals for each plane.
	//createNormals();
}

void drawBorder() {
	glPushAttrib(GL_LIGHTING_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	int len = 2 * (Interactivity::getLength() + 4) + 8;

	switch (Interactivity::getLevel()) {
		case 1:
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glTranslatef(-8,-6,3);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(-14,-6,3);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			break;
		case 2:
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glTranslatef(-8,-6,5);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(-18,-6,5);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			break;
		case 3:
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glTranslatef(-8,-6,7);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			
			glColor3ub(244, 67, 54); //red colour
			glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(-22,-6,7);
			glScalef(0.5,13,len);
			glutSolidCube(1);
			glPopMatrix();
			break;
	}
	
	glDisable(GL_COLOR_MATERIAL);
	glPopAttrib();
}

void drawBoard() {
	// Ignore lighting
	glPushAttrib(GL_LIGHTING_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	float m_specular[] = {0.1, 0.1, 0.1, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);

	int len = Interactivity::getLength();
	// colours
	unsigned char blue[] = {33, 150, 243};
	unsigned char yellow[] = {255, 235, 59};
	Structure::point3D* beenTo = Interactivity::getPlayerBeen();

	for(int i = 0; i < len; ++i) {
		for(int j = 0; j < len - i; ++j) {
			bool contains = false;
			// Check if the player has landed on the spot
			for (int k = 0; k < 50; ++k) {
				if (beenTo[k].x == i * 2 && beenTo[k].z == j * 2 + i * 2) {
					contains = true;
					break;
				}
			}
			// Set block to black if the player has landed on it
			glColor3ubv(contains ? yellow : blue);
			glPushMatrix();
				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glutSolidCube(2);

				// Draw column
				for (int k=-12; k<j * 2; k+=2) {
					glTranslatef(0, -2, 0);
					glutSolidCube(2);
				}
			glPopMatrix();
		}
	}
	glDisable(GL_COLOR_MATERIAL);
	glPopAttrib();
}

void resetArray(int size) {
	for(int x = 0; x < size; x++){
        for(int z = 0; z < size; z++){
        	waterHeightMap[x][z] = 0.0;
		}
	}
}

void drawWater(int step) {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);	// So the materials don't affect other stuff
	glTranslatef(-8, -2, -8);

	int len = 2 * (Interactivity::getLength() + 4) + 8;

	if (getSandHeight) {		// Initial load
		getSandHeight = !getSandHeight;
		createWaves(3, len);
	}

	if (step % 40 == 0) {	// the waves
		resetArray(len);
		createWaves(3, len);
	}

	//material to make water plane look like water.
	float m_ambient[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	float m_diff[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
	float m_specular[] = {0, 0.501, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	float m_shiny = 0.25f;
	glMaterialf(GL_FRONT, GL_SHININESS, m_shiny);

	// draws the water plane.
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			glBegin(GL_QUAD_STRIP);
			glNormal3f(0, 1, 0);

			glVertex3f(i    , waterHeightMap[i][j + 1]    , j + 1);
			glVertex3f(i + 1, waterHeightMap[i + 1][j + 1], j + 1);
			glVertex3f(i    , waterHeightMap[i][j]        , j    );
			glVertex3f(i + 1, waterHeightMap[i + 1][j]    , j    );
			glEnd();
		}
	}
	glPopAttrib();
	glPopMatrix();
}

void drawSand() {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);	// So the materials don't affect other stuff
	glTranslatef(-8, -12, -8);

	int len = 2 * (Interactivity::getLength() + 4) + 8;
	if(getSandHeight) {		// Initial load
		getSandHeight = !getSandHeight;
		createSlopes(2, len);
	}
	float amb[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	float diff[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	float spec[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);

	//draws the sand plane.
	for(int i = 0; i < len; i++) {
		for(int j = 0; j < len; j++) {
			glBegin(GL_QUAD_STRIP);
			glNormal3f(0, 1, 0);
			glVertex3f(i    , sandHeightMap[i][j + 1],     j + 1);
			glVertex3f(i + 1, sandHeightMap[i + 1][j + 1], j + 1);
			glVertex3f(i    , sandHeightMap[i][j],         j    );
			glVertex3f(i + 1, sandHeightMap[i + 1][j],     j    );
			glEnd();	
		}
	}
	glPopAttrib();
	glPopMatrix();
}

// Draws everything except the player/enemies
void Environment::drawEnvironment(int step) {
	drawSand();
	drawBoard();
	drawBorder();
	drawWater(step);
}