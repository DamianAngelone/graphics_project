#include "UserInterface.h"
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
#include "Interactivity.h"

// draws the player and calls the necessary logic functions
void UserInterface::drawUI() {
	
}