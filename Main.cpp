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
#include <cmath>
using namespace std;

// Include project files
#include "Structure.h"
#include "Environment.h"
#include "Interactivity.h"
#include "Player.h"
#include "Enemy.h"
#include "UserInterface.h"

bool pause = false;				// If the game is paused
bool fromIntro = false;			// If game is currently in the intro 

const int WIDTH = 960;			// Width of the screen
const int HEIGHT = 540;			// Length of the screen
const int STEPSPEED = 500;		// Sets enemy movement speed
const int ENEMYSPEED = 300;
int step = 0;					// When to make the game step
int enemyStep = 0;				// When to make the enemy step on level 3
int clockTimer = 0;				// For the HUD timer
int timesUp = false;				// If game runs out of time
int skyWidth, skyHeight, skyMaxi;	// For the textures (intro, sky, & walls)
GLuint skyBoxTexture[2];			// For sky textures

GLubyte* skyImage0;			//Intro texture
GLubyte* skyImage1;			//Sky texture

// Used for the mouse functions
int xOrigin = 0;			// The x origin for mouse dragging
int yOrigin = 0;			// The y origin for mouse dragging
float angle = 0.0f;				// X angle for mouse dragging	
float angle2 = 0.0f;			// Y angle for mouse dragging
float lx = 0.0f, lz = 0.0f;		// Variabels for altering glLookAt()
float deltaAngle = 0.0f;		// X angle variable (horizontal)
float deltaAngle2 = 0.0f;		// X angle variable (vertical)

/* Callback for when the mouse clicks */
void mouse(int btn, int state, int x, int y) {
	// Sets coordinates of where the mouse was clicked
	int mouseX = x; 
	int mouseY = 540 - y;
	// If the left button is being used
	if(btn == GLUT_LEFT_BUTTON){
		// If the left button is being released
		if(state == GLUT_UP){
			// Reset current mouse angle and disallows mouseMouse from running
			lx = 0;
			lz = 0;
			angle = 0;
			xOrigin = -1;
			yOrigin = -1;
		}
		// If the left button is being pressed
		else {
			// Sets current x-/y- coordinates of the mouse as the cooridinates to be used for calculation
			xOrigin = x;
			yOrigin = y;
		}
	}
}

/* Callback for when the mouse is moving */
void mouseMove(int x, int y) {
	// If the left button is being pressed (no released).
	if (xOrigin >= 0) {
		// Calculates the the distance the camera will move when the mouse is moved.
		deltaAngle = (x - xOrigin) * 0.001f;
		deltaAngle2 = (y - yOrigin) * 0.001f;
		lx = sin(angle - deltaAngle) * 70;
		lz = sin(angle - deltaAngle2) * 90;
	}
}

/* Draws the texture for the intro and sky */
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
    glBindTexture(GL_TEXTURE_2D,
    	skyBoxTexture[UserInterface::getIntroState() ? 1 : 0]);
	glColor4f(1, 1, 1, 1);

	// Draws the quad that the texture is drawn on
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

/* Callback for when the program draws */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw textures
	skybox();

	// Screen attributes 
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	// Camera
	Structure::point3D eye = Interactivity::getEye();
	Structure::point3D center = Interactivity::getCenter();
	gluLookAt(eye.x, eye.y, eye.z, center.x + lx, center.y, center.z + lz, 0, 1, 0);
	glShadeModel(GL_SMOOTH);

	// Scene
	float lightPos[] = {eye.x, eye.y, eye.z, 1};
 	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	// Draws the UI if the intro isn't currently happening
 	if(UserInterface::getIntroState()){
 		UserInterface::drawUI();
 	}
 	// If no intro is occuring, draw the intro texture and display it's text
	else {
		if (!fromIntro) {
			fromIntro = true;
			glBindTexture(GL_TEXTURE_2D, skyBoxTexture[0]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		    // Gets and saves skyImage0
		    skyImage0 = Interactivity::loadPPM("images/mat.ppm", &skyWidth, &skyHeight, &skyMaxi);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyWidth, skyHeight, 0, GL_RGB,
	                 GL_UNSIGNED_BYTE, skyImage0);
		}

		glPushMatrix();
			// Rotation of the camera affects the whole game world
			glRotatef(Interactivity::getTheta(), 0, 1, 0);
			// Draw player
			Player::drawPlayer(step > STEPSPEED);
			// Draw the enemies for level 2
			if (Interactivity::getLevel() == 2 &&
				!UserInterface::getFinishedLevelState() &&
				!UserInterface::getWinGameState()) {
				Interactivity::enemy[0].drawEnemy(step > STEPSPEED);
			}
			// Draw the enemies for level 3
			else if (Interactivity::getLevel() == 3 &&
				!UserInterface::getFinishedLevelState() &&
				!UserInterface::getWinGameState()) {
				Interactivity::enemy[0].drawEnemy(enemyStep > ENEMYSPEED);
				Interactivity::enemy[1].drawEnemy(enemyStep > ENEMYSPEED);
			}
			// Draw the environment
			Environment::drawEnvironment(step);
			// Draw the game UI
			UserInterface::drawUI();
		glPopMatrix();

		// Check to see if the player is on the same block as an enemy
		if (Interactivity::getLevel() > 1 && Interactivity::getSpace() == 0)
			Interactivity::checkIntersections();
		// Whenever this clock completes a cylce the in-game decreases in value 	
		if (step > STEPSPEED) {		
			step = 0;
			clockTimer = 0;
			UserInterface::decrTime();
		}
		// Whenever this clock completes a cylce the enemies move and the global 
		if (enemyStep > ENEMYSPEED)
			enemyStep = 0;
		// Check if the in-game clock hasfun out of time
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
// Initialize all starting values
void init() {
	UserInterface::readHighScore();
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
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);  
	// Sets up camera with proper matrix mode
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, WIDTH / HEIGHT, 1, 400);
	srand(time(0));
	// Textures
    glEnable(GL_TEXTURE_2D);
    glGenTextures(2, skyBoxTexture);
    // Set the skyImage0 parameters
    glBindTexture(GL_TEXTURE_2D, skyBoxTexture[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Gets and saves skyImage0
    skyImage1 = Interactivity::loadPPM("images/start.ppm", &skyWidth, &skyHeight, &skyMaxi);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyWidth, skyHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, skyImage1);
   	Environment::setTextures();
    glMatrixMode(GL_TEXTURE);
    // Default call
	redraw(0);
}
// The main function (contains callbacks, window proeprties, and all display initializations)
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