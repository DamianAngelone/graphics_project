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
#include "UserInterface.h"

// Parameters for fish position
float Fishes[3][6] = {{4,-9,0,0,30,0}, {7,-5,0,0,-20,0}, {6,-3,0,0,90,0}};
int InitFishPosit = 0;
// Keeps track if fish collide with water/sand path 
bool getWaterHeight = true;
bool getSandHeight = true;
// Used to texture bricks
int brickWidth, brickHeight, brickMaxi;	
GLuint brickTexture[1];
// Sets up the grids for water/sand
float waterHeightMap[100][100];
float sandHeightMap[100][100];
// Used for brick textures
GLubyte* brickImage;

/* Sets up textures for bricks */
void Environment::setTextures() {
	glGenTextures(2, brickTexture);
    
    // Set the brickImage parameters
    glBindTexture(GL_TEXTURE_2D, brickTexture[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Loads in the .ppm file for textures
	brickImage = Interactivity::loadPPM("brick.ppm", &brickWidth, &brickHeight, &brickMaxi);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brickWidth, brickHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, brickImage);
}

/* Creates the real-time waves for water */
void createWaves(int iterations, int size) {
	// Will run for how many hills was specified by the user. 
	for(int i = 0; i < iterations; i++){

		int center_X = rand() % size; 			// Water Grid (x) midpoint of circle                      
	    int center_Z = rand() % size;			// Water Grid (z) midpoint of circle
	    float terrainCircleSize = 35; 				// Random radius of circle
	    int randomHeight = (rand() % 1) + 1;		// Random height for slope   
	    
	    // Will run for every vertex in the grid.
        for(int x = 0; x < size; x++){
            for(int z = 0; z < size; z++){
            	// Performs the circles algorithm
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
}

/* Sets up slopes for sand */
void createSlopes(int iterations, int size) {
	// Will run for how many hills was specified by the user. 
	for(int i = 0; i < iterations; i++){
		int center_X = rand() % size; 				// Sand grid (x) midpoint of circle (1-gridLength)                      
	    int center_Z = rand() % size;				// Sand grid (z) midpoint of circle (1-gridWidth)
	    float terrainCircleSize = 30; 				// Random radius of circle (1-5)
	    int randomHeight = (rand() % 4) + 1;		// Random height for slope (1-5)   
	    
	    // Will run for every vertex in the grid.
        for(int x = 0; x < size; x++){
            for(int z = 0; z < size; z++){
            	// Performs the circles algorithm
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
}

/* Draws in the texture for the wall */
void drawWall() {
	glColor4f(1, 1, 1, 1);
	glScalef(0.112, 0.034, 0);
	glBegin(GL_QUADS);
	    glTexCoord3f(0, 0, 0);
	    glVertex3f(0, 0, 0);
	    glTexCoord3f(1, 0, 0);
	    glVertex3f(265, 0, 0);
	    glTexCoord3f(1, 1, 0);
	    glVertex3f(265, 398, 0);
	    glTexCoord3f(0, 1, 0);
	    glVertex3f(0, 398, 0);
    glEnd();
}

/* Draws the wall mesh */
void drawBorder() {
	glEnable(GL_TEXTURE_2D); 
	glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, brickTexture[0]);
	
	float trans[5][3];
	trans[0][0] = -8.3;
	trans[0][1] = -6;
	trans[0][2] = 7.4;

	trans[1][0] = -8;
	trans[1][1] = -13;
	trans[1][2] = 21.5;

	trans[2][0] = -8.6;
	trans[2][1] = -13;
	trans[2][2] = -8;

	trans[3][0] = 7;
	trans[3][1] = -6;
	trans[3][2] = 22.5;

	trans[4][0] = 22;
	trans[4][1] = -13;
	trans[4][2] = 21.95;

	// Right block
	glPushMatrix();
		glColor3ub(194, 117, 87);
		glTranslatef(trans[0][0], trans[0][1], trans[0][2]);
		glScalef(0.5, 13, 30.7);
		glutSolidCube(1);
	glPopMatrix();
	// Right texture front
	glPushMatrix();
		glTranslatef(trans[1][0], trans[1][1], trans[1][2]);
		glRotatef(90, 0, 1, 0);
		drawWall();
	glPopMatrix();
	// Right texture back
	glPushMatrix();
		glTranslatef(trans[2][0], trans[2][1], trans[2][2]);
		glRotatef(270, 0, 1, 0);
		drawWall();
	glPopMatrix();
	// Left block
	glPushMatrix();
		glColor3ub(194, 117, 87);
		glTranslatef(trans[3][0], trans[3][1], trans[3][2]);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 13, 30);
		glutSolidCube(1);
	glPopMatrix();
	// Left texture front
	glPushMatrix();
		glTranslatef(trans[4][0], trans[4][1], trans[4][2]);
		glRotatef(180, 0, 1, 0);
		drawWall();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

/* Draws the baord that the game takes place on */
void Environment::drawBoard() {
	// Ignore lighting
	glPushAttrib(GL_LIGHTING_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// Material lighting settings
	float m_specular[] = {0.1, 0.1, 0.1, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	// Length of the board for the current level
	int len = Interactivity::getLength();
	// Colours for the board.
	unsigned char blue[] = {33, 150, 243};
	unsigned char yellow[] = {255, 235, 59};
	Structure::point3D* beenTo = Interactivity::getPlayerBeen(); // If the player visits the block
	// Checks all block in the current level
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
			// Set block to yellow if the player has landed on it
			glColor3ubv(contains ? yellow : blue);
			glPushMatrix();
				// Draws the rows
				glTranslatef(i * 2, j * 2, j * 2 + i * 2);
				glutSolidCube(2);
				// Draws the columns
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

/* Resets the water array (used to create waves) */
void resetArray(int size) {
	for(int x = 0; x < size; x++){
        for(int z = 0; z < size; z++){
        	waterHeightMap[x][z] = 0.0;
		}
	}
}

/* Draws the transparent quad strip for the water */
void drawWater(int step) {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);	// Prevents the materials from affecting other stuff
	glTranslatef(-8, -3, -8);
	// Initial load of sand
	if (getSandHeight) {		
		getSandHeight = !getSandHeight;
		createWaves(3, 30);
	}
	// Initial load of the waves
	if ((step % 40 == 0 && !UserInterface::calculatingScore())) {	
		resetArray(30);
		createWaves(3, 30);
	}
	// Material to make water plane look like water
	float m_ambient[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	float m_diff[] = {0, 0.509, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
	float m_specular[] = {0, 0.501, 0.501, 0.75};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	float m_shiny = 0.25f;
	glMaterialf(GL_FRONT, GL_SHININESS, m_shiny);

	// Draws the water plane
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			glBegin(GL_QUAD_STRIP);
			glNormal3f(0, 1, 0);
			//Draws the quad strip
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

/* Draws the quad strip for the sand */
void drawSand() {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);	// So the materials don't affect other stuff
	glTranslatef(-8, -12, -8);
	// Initial load of the sand
	if(getSandHeight) {		
		getSandHeight = !getSandHeight;
		createSlopes(2, 30);
	}
	float amb[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	float diff[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	float spec[] = {0.6274, 0.3216, 0.1764, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	// Draws the sand plane
	for(int i = 0; i < 30; i++) {
		for(int j = 0; j < 30; j++) {
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

/* Initializes where the fish will start */
void InitFishPosition(void){
	for(int i = 0 ; i < 3 ; i++){
		Fishes[i][0] = rand() % 5;
		Fishes[i][4] = rand() % 360 ; 
	}
	InitFishPosit = 1 ;
}

/* Draws the fish to the scene */
void drawFish(int n) {	
	int len = Interactivity::getLength()*2;
	
	glPushMatrix();
		glRotatef((n == 1 ? 1 : -1) * Fishes[n][4], 0, 1, 0);
		glTranslatef(Fishes[n][0]+len,Fishes[n][1],0);
			glPushMatrix();
			glRotatef((n == 1 ? 180 : 0), 0, 1, 0);
			glScalef(0.5,0.5,0.5);
			// Draw body
			glColor3f(0,0,1);
			glScalef(1,1,1.5);
			glutSolidSphere(1, 100, 100);
			// Right eye
			glPushMatrix();
				glScalef(1,1,0.66);
				glTranslatef(-0.35,0.3,1.1);	
				glColor3f(1,1,1);
				glutSolidSphere(0.4, 100, 100);
				// Right pupil
				glPushMatrix();
					glTranslatef(0,0,0.3);
					glColor3f(0,0,0);
					glutSolidSphere(0.2,100,100);
				glPopMatrix();
			glPopMatrix();
			
			// Left eye
			glPushMatrix();
				glScalef(1,1,0.66);
				glTranslatef(0.35,0.3,1.1);	
				glColor3f(1,1,1);
				glutSolidSphere(0.4, 100, 100);
				// Left pupil
				glPushMatrix();
					glTranslatef(0,0,0.3);
					glColor3f(0,0,0);
					glutSolidSphere(0.2,100,100);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glColor3f(0,0,1);
				glScalef(0.8,0.8,0.8);
				// Tail
				glTranslatef(0,0,-2);
				int flip = rand()%2;
				glRotatef((flip == 1? 10 : -10),0,1,0);
				glutSolidCone(1, 1, 100, 100);
			glPopMatrix();
		glPopMatrix();
		
	glPopMatrix();
}

/* Gives the fish movement during the game */
void renderFish(int step){
	// Initialize fish position
	if(InitFishPosit == 0) {
		InitFishPosition();		
	}
	else {
		int len = Interactivity::getLength();
		glPushMatrix();
		glScalef(0.7, 0.7, 0.7);
		if (step % 1 == 0) {
			// draw each fish
			for(int i  = 0; i < 3 ; i++){
				glPushMatrix();
				glTranslatef(len,0,len);
				switch(i) {	// set the speeds
					case 0:
						Fishes[i][4] += 1;	// rotation speed
						break;
					case 1:
						Fishes[i][4] += 0.3;	// rotation speed
						break;
					case 2:
						Fishes[i][4] += 0.6;	// rotation speed
						break;
				}
				drawFish(i);
				glPopMatrix();
			}
		}
		glPopMatrix();
	}
}

/* Draws everything except for the player and the enemies */
void Environment::drawEnvironment(int step) {
	drawSand();
	Environment::drawBoard();
	drawBorder();
	// Sets up lighting accordingly
	glDisable(GL_LIGHTING);
	renderFish(step);
	glEnable(GL_LIGHTING);
	drawWater(step);
}
