//opengl cross platform includes
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
#include <ctime>
using namespace std;

// Include project files
#include "Structure.h"
#include "Environment.h"
#include "Interactivity.h"
#include "Player.h"
#include "Enemy.h"
#include "UserInterface.h"

bool pause = false;		// if the game is paused

const int WIDTH = 960;
const int HEIGHT = 540;
const int STEPSPEED = 500;
const int ENEMYSPEED = 200;
int step = 0;			// When to make the game step
int enemyStep = 0;		// When to make the enemy step on level 3
int clockTimer = 0;		// For the HUD timer
int timesUp = false;
int skyWidth, skyHeight, skyMaxi;	// For the texture
GLuint skyBoxTexture[1];

GLubyte* skyImage;

// Got started with: 
// https://www.opengl.org/discussion_boards/showthread.php/176629-Background-image-behind-3D-scene
void skybox() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw the skybox
	glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, skyBoxTexture[0]);
	glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);
	    glTexCoord2f(0.0, 0.0);
	    glVertex2f(0.0, 0.0);
	    glTexCoord2f(1.0, 0.0);
	    glVertex2f(WIDTH, 0.0);
	    glTexCoord2f(1.0, 1.0);
	    glVertex2f(WIDTH, HEIGHT);
	    glTexCoord2f(0.0, 1.0);
	    glVertex2f(0.0, HEIGHT);
    glEnd();

    glDisable(GL_TEXTURE_2D);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, WIDTH / HEIGHT, 1, 400);
}

void display(void) {
	//glClearColor(95.0/255, 195.0/255, 240.0/255, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	// Camera
	Structure::point3D eye = Interactivity::getEye();
	Structure::point3D center = Interactivity::getCenter();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0, 1, 0);
	glShadeModel(GL_SMOOTH);

	// Scene
	float lightPos[] = {eye.x, eye.y, eye.z, 1};
 	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
 	if(UserInterface::getIntroState()){
 		UserInterface::drawUI();
 	}

		else if(!UserInterface::getIntroState()){

			glPushMatrix();
			// Rotation of the camera affects the whole game world
			glRotatef(Interactivity::getTheta(), 0, 1, 0);

			Player::drawPlayer(step > STEPSPEED);
			// Draw the enemies
			if (Interactivity::getLevel() == 2 &&
				!UserInterface::getFinishedLevelState() &&
				!UserInterface::getWinGameState()) {
				Interactivity::enemy[0].drawEnemy(step > STEPSPEED);
			}
			else if (Interactivity::getLevel() == 3 &&
				!UserInterface::getFinishedLevelState() &&
				!UserInterface::getWinGameState()) {
				Interactivity::enemy[0].drawEnemy(enemyStep > ENEMYSPEED);
				Interactivity::enemy[1].drawEnemy(enemyStep > ENEMYSPEED);
			}
			Environment::drawEnvironment(step);
			UserInterface::drawUI();

		glPopMatrix();
		
		// Check to see if the player is on the same block as an enemy
		if (Interactivity::getLevel() > 1 && Interactivity::getSpace() == 0)
			Interactivity::checkIntersections();
			
		if (step > STEPSPEED) {		// time to reset
			step = 0;
			clockTimer = 0;
			UserInterface::decrTime();
		}

		if (enemyStep > ENEMYSPEED)
			enemyStep = 0;

		if ((UserInterface::getTime() == 0) && !timesUp && !UserInterface::calculatingScore()) {
			UserInterface::setGameOverState();
			timesUp = !timesUp;
		}
	}
	glutSwapBuffers();
}

// Constantly redraw the screen every 17 ms for 60 fps
void redraw(int i) {
	if (!pause) {
		glutPostRedisplay();
		step += 17;
		clockTimer += 17;
		enemyStep += 17;
		glutTimerFunc(17, redraw, 0);
	}
}

void init() {
	// No transparency
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE_ARB);	// anti-aliasing
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightColour[] = {1.0, 0.9215, 0.2509, 1};	// #FFEB3B
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glShadeModel(GL_FLAT);

	// Callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(Interactivity::keyboard);
	glutSpecialFunc(Interactivity::special);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, WIDTH / HEIGHT, 1, 400);
	srand(time(0));

	/* TEXTURES */
    glEnable(GL_TEXTURE_2D);
    glGenTextures(2, skyBoxTexture);
    
    /* Set the skyImage parameters*/
    glBindTexture(GL_TEXTURE_2D, skyBoxTexture[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    /*Get and save skyImage*/
    skyImage = Interactivity::loadPPM("mat.ppm", &skyWidth, &skyHeight, &skyMaxi);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyWidth, skyHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, skyImage);
   	Environment::setTextures();
    
    glMatrixMode(GL_TEXTURE);

	redraw(0);
}

int main(int argc, char** argv) {
	Interactivity::printInstructions();
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow("Project");
	init();
	glutMainLoop();
	return(0);
}