#include <stdlib.h>
#include <GLUT/glut.h>
#include <stdio.h>

#include "utilitaire.h"

#define FLEN 10

void affichage(void);
void keyboard(char key);
void calculs(void);
void quit(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Test"); 
	glutDisplayFunc(affichage);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(FLEN, calculs, 0);
	glutMainLoop();
}

void affichage(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0, 4.0, 0, 4.0, -1, 1);
}

void keyboard(char key) {
	switch (key) {
		case 27:
			quit();
			break;
	}
}

void calculs(void) {
	
	glutPostRedisplay();
	glutTimerFunc(FLEN, calculs, 0);
}

void quit(void) {
	glutDestroyWindow(1);
	exit(0);
}
