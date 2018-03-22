#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glui.h>

extern "C" {
	#include "read.h"
	#include "robot.h"
	#include "particle.h"
	#include "model.h"
	#include "graphic.h"
	#include "constantes.h"
}

#define WIDTH 800
#define HEIGHT 800


static void affichage(void);
static void reshape(int w, int h);
static void keyboard(char key);
static GLUI win;

int main(int argc, char ** argv) {
	
	if (argc > 1) {
		if(read_file(argv[1])) {
			robot_print();
			particle_print();
			initial_collisions();
		}
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("ROBOTS");
	glViewport(0, 0, WIDTH, HEIGHT);
	glOrtho(-DMAX, DMAX, -DMAX, DMAX, -1, 1);
	glutDisplayFunc(graphic_affichage);
	glutReshapeFunc(graphic_reshape);
	glutIdleFunc(graphic_affichage);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutMainLoop();
	
	
	return EXIT_SUCCESS;
}



static void keyboard(char key) {
	switch (key) {
		case 27:
			glutDestroyWindow(1);
			exit(0);
			break;
		
	}
}


