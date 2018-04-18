#include <stdio.h>
#include <math.h>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "utilitaire.h"
#include "graphic.h"
#include "constantes.h"
#include "robot.h"
#include "particle.h"

#define R_RES 24
#define POSX 200
#define POSY 200
#define THICK 1.5
#define NORMAL 1.0

#define COLOR_LIGHT_BLUE 	0.5f, 0.5f, 1.0f
#define COLOR_DARK_BLUE 	0.0f, 0.0f, 0.5f
#define COLOR_BLACK 		0.0f, 0.0f, 0.0f
#define COLOR_VOMIT_GREEN 	0.6f, 0.7f, 0.6f
#define COLOR_LIGHT_GRAY 	0.2f, 0.2f, 0.2f
#define COLOR_GRAY 			0.5f, 0.5f, 0.5f


static double ratio;

int graphic_init_glut(int * argc, char ** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(POSX, POSY);
	glutInitWindowSize(WIDTH,HEIGHT);
	int g_window = glutCreateWindow("ROBOTS");
	glViewport(0, 0, WIDTH, HEIGHT);
	glOrtho(-DMAX, DMAX, -DMAX, DMAX, -1, 1);
	glutDisplayFunc(graphic_affichage);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	return g_window;
}

void graphic_affichage(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	graphic_border();
	int nb_robot = robot_get_nb();
	robot_get_init_i(nb_robot-1);
	double x, y, a, r;
	for(int i = 0; i < nb_robot; i++){
		robot_get(&x, &y, &a, NULL, NULL);
		graphic_robot(x, y, a);
	}
	int nb_particle = particle_get_nb();
	particle_get_init_i(nb_particle-1);
	for(int i = 0; i < nb_particle; i++){
		particle_get(NULL, &r, &x, &y, NULL, NULL);
		graphic_particle(r, x, y);
	}	
	glutSwapBuffers();
}

void graphic_reshape(int w, int h){
	glViewport(0, 0, w, h);
	if(h == 0)
		h = 1;
	ratio = (double) w / (double) h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(ratio >= 1.)
		glOrtho(-DMAX*ratio, DMAX*ratio, -DMAX, DMAX, -1, 1);
	if(ratio < 1.)
		glOrtho(-DMAX, DMAX, -DMAX/ratio, DMAX/ratio, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void graphic_robot(double x, double y, double angle){
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glRotated(angle, 0.0, 0.0, 1.0);
	glColor3f(COLOR_LIGHT_BLUE);
	glBegin(GL_POLYGON);
	for(double i = M_PI/4; i < M_PI*7/4; i += 2*M_PI/R_RES){
		glVertex2d(R_ROBOT*cos(i), R_ROBOT*sin(i));
	}
	glVertex2d(R_ROBOT, 0.0);
	glEnd();
	glColor3f(COLOR_DARK_BLUE);
	glBegin(GL_LINE_LOOP);
	for(double i = M_PI/4; i < M_PI*7/4; i += 2*M_PI/R_RES){
		glVertex2d(R_ROBOT*cos(i), R_ROBOT*sin(i));
	}
	glVertex2d(R_ROBOT, 0.0);
	glEnd();
	glColor3f(COLOR_BLACK);
	glLineWidth(THICK);
	glBegin(GL_LINES);
		glVertex2d(0.0, 0.0);
		glVertex2d(R_ROBOT, 0.0);
	glEnd();
	glLineWidth(NORMAL);
}

void graphic_particle(double r, double x, double y){
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glColor3f(COLOR_VOMIT_GREEN);
	glBegin(GL_POLYGON);
	for(double i = 0; i < 2.0*M_PI; i += 2*M_PI/R_RES){
		glVertex2d(r*cos(i), r*sin(i));
	}
	glEnd();
	glColor3f(COLOR_LIGHT_GRAY);
	glBegin(GL_LINE_LOOP);
	for(double i = 0; i < 2.0*M_PI; i += 2*M_PI/R_RES){
		glVertex2d(r*cos(i), r*sin(i));
	}
	glEnd();
}

void graphic_border(void){
	glLoadIdentity();
	glLineWidth(1);
	glColor3f(COLOR_GRAY);
	glBegin(GL_LINE_LOOP);
	glVertex2d(DMAX, DMAX);
	glVertex2d(DMAX, -DMAX);
	glVertex2d(-DMAX, -DMAX);
	glVertex2d(-DMAX, DMAX);
	glEnd();
}


