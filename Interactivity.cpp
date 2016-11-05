#include "Interactivity.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Interactivity::keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':						// Quit the program
		case 'Q':
		case 27:
			exit(0);
			break;
	}
}

void Interactivity::special(unsigned char key, int x, int y) {
	switch (key) {
	}
}

void Interactivity::printInstructions() {
	cout << "-----------------------------------"  << endl;
	cout << "INSTRUCITONS: " << endl;
	cout << "KEY     ACTION" << endl;
	cout << "Q       Quit"   << endl;
	cout << "ESC"            << endl;
	cout << "-----------------------------------"  << endl;
}