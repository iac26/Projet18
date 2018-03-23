#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
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
static int g_window;
static void quit(void);

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
	g_window = glutCreateWindow("ROBOTS");
	glViewport(0, 0, WIDTH, HEIGHT);
	glOrtho(-DMAX, DMAX, -DMAX, DMAX, -1, 1);
	glutDisplayFunc(graphic_affichage);
	glutReshapeFunc(graphic_reshape);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	GLUI * glui = GLUI_Master.create_glui("CONTROL", 0, 900, 200);
	
	new GLUI_StaticText(glui, "TEEEEESTEUH");
	
	new GLUI_Button(glui, "EXIT", 0, (GLUI_Update_CB)quit);
	
	glui->set_main_gfx_window(g_window);
	
	GLUI_Master.set_glutIdleFunc(NULL);
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

static void quit(void) {
	glutDestroyWindow(g_window);
	exit(0);
}


