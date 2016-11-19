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

unsigned char colours[6][4] = {{244, 67,  54, 1},		// Red
		                   	   {33,  150, 243,1 },		// Blue
		                   	   {0,   150, 36, 1},		// Teal
		                   	   {1,   193, 7, 1},		// Amber
		                   	   {158, 158, 158, 1},		// Gray
		                       {205, 220, 57, 1}};		// Lime

bool getWaterHeight = true;
bool getSandHeight = true;
		                       
int blocks[3] = {3, 5, 8};		// Number of blocks in a row for each level

float WaterHeightMap[100][100];
float SandHeightMap[100][100];

// Get the number of blocks in a row
int Environment::getLength() {
	return blocks[Interactivity::getLevel() - 1];
}

void createWaves(int iterations, int size){

	//will run for how many hills was specified by the user. 
	for(int i = 0; i < iterations; i++){

		int center_X = rand() % size; 				//GRID (x) midpoint of circle (1-gridLength)                      
	    int center_Z = rand() % size;				//GRID (z) midpoint of circle (1-gridWidth)
	    float terrainCircleSize = 30; 				//random radius of circle (1-5)
	    int randomHeight = (rand() % 3) + 1;		//random height for slope (1-5)   
	    
	    //will run for every vertex in the grid.
        for(int x = 0; x < size; x++){
            for(int z = 0; z < size; z++){

				float distanceFromX = x - center_X;
                float distanceFromZ = z - center_Z;
                float totalDistance = sqrtf((distanceFromX * distanceFromX) + (distanceFromZ * distanceFromZ));
                float pd = (totalDistance * 2) / terrainCircleSize;

                if (fabs(pd) <= 1.0){
             	
                	WaterHeightMap[x][z] += randomHeight / 2.0 + cos(pd * 3.14) * randomHeight / 2.0;
                }
            }
        } 
	}
	//create normals for each plane.
	//createNormals();
}

void createSlopes(int iterations, int size){


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

                if (fabs(pd) <= 1.0){
             	
                	SandHeightMap[x][z] += (randomHeight / 2.0 + cos(pd * 3.14) * randomHeight / 2.0);
                }
            }
        } 
	}
	//create normals for each plane.
	//createNormals();
}

void drawBoard(){

	int len = blocks[Interactivity::getLevel() - 1];
	int max = sizeof(colours)/sizeof(colours[0]) - 1, 
		colour = max;
	for (int i=0; i<len; ++i) {
		for (int j=0; j<len - i; ++j) {

			float amb[] = {colours[colour][0]/150, colours[colour][1]/150, colours[colour][2]/150, 1}; 
			glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
			glPushMatrix();

				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glutSolidCube(2);

				// Draw column
				for (int k=-8; k<j * 2; k+=2) {
					glTranslatef(0, -2, 0);
					glutSolidCube(2);
				}
				--colour;
				if (colour == -1)
					colour = max;
			glPopMatrix();
		}
	}
}

void resetArray(int size){

	for(int x = 0; x < size; x++){
        for(int z = 0; z < size; z++){

        	WaterHeightMap[x][z] = 0.0;
		}
	}
}

void drawWater(int step){

	glPushMatrix();
	//glTranslatef(0, -0.25, 0);

	int len = 2*(Environment::getLength() + 4);

	if(getSandHeight){
		getSandHeight = !getSandHeight;
		createWaves(3, len);
	}

	if(step % 5 == 0){
		createWaves(3, len);
		resetArray(len);
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


	//draws the water plane.
	for(int i = -8; i < len; i++){
		for(int j = -8; j < len; j++){

			glBegin(GL_QUAD_STRIP);

			glNormal3f(0, 1, 0);

			glVertex3f(i    , WaterHeightMap[i][j+1], j + 1);
			glVertex3f(i + 1, WaterHeightMap[i+1][j+1], j + 1);
			glVertex3f(i    , WaterHeightMap[i][j], j    );
			glVertex3f(i + 1, WaterHeightMap[i+1][j], j    );
			glEnd();	
		}
	}
	glPopMatrix();
}

void drawSand(){

	glPushMatrix();
	glTranslatef(0, -8, 0);

	int len = 2*(Environment::getLength() + 4);

	if(getSandHeight){
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
	for(int i = -8; i < len; i++){
		for(int j = -8; j < len; j++){

			glBegin(GL_QUAD_STRIP);

			glNormal3f(0, 1, 0);
		
			glVertex3f(i    , SandHeightMap[i][j+1], j + 1);
			glVertex3f(i + 1, SandHeightMap[i+1][j+1], j + 1);
			glVertex3f(i    , SandHeightMap[i][j], j    );
			glVertex3f(i + 1, SandHeightMap[i+1][j], j    );
			glEnd();	

		}
	}
	glPopMatrix();
}

// Draws everything except the player/enemies
void Environment::drawEnvironment(int step) {

	drawSand();
	drawBoard();
	drawWater(step);
}