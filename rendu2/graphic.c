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

#define R_RES 24

static double ratio;

void graphic_affichage(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	graphic_border();
	
	int nb_robot = robot_get_nb();
	robot_get_init_i(nb_robot-1);
	double x, y, a, r;
	for(int i = 0; i < nb_robot; i++) {
		robot_get(&x, &y, &a, NULL, NULL);
		graphic_robot(x, y, a);
	}
	
	int nb_particle = particle_get_nb();
	particle_get_init_i(nb_particle-1);
	for(int i = 0; i < nb_particle; i++) {
		particle_get(NULL, &r, &x, &y, NULL, NULL);
		graphic_particle(r, x, y);
	}
	
	glutSwapBuffers();
}

void graphic_reshape(int w, int h) {
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

void graphic_robot(double x, double y, double angle) {
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glRotated(angle, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_POLYGON);
	for(double i = M_PI/4; i < M_PI*7/4; i += 2*M_PI/R_RES) {
		glVertex2d(R_ROBOT*cos(i), R_ROBOT*sin(i));
	}
	glVertex2d(R_ROBOT, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_LINE_LOOP);
	for(double i = M_PI/4; i < M_PI*7/4; i += 2*M_PI/R_RES) {
		glVertex2d(R_ROBOT*cos(i), R_ROBOT*sin(i));
	}
	glVertex2d(R_ROBOT, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
		glVertex2d(0.0, 0.0);
		glVertex2d(R_ROBOT, 0.0);
	glEnd();
}

void graphic_particle(double r, double x, double y) {
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glColor3f(0.6, 0.7, 0.6);
	glBegin(GL_POLYGON);
	for(double i = 0; i < 2.0*M_PI; i += 2*M_PI/R_RES) {
		glVertex2d(r*cos(i), r*sin(i));
	}
	glEnd();
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINE_LOOP);
	for(double i = 0; i < 2.0*M_PI; i += 2*M_PI/R_RES) {
		glVertex2d(r*cos(i), r*sin(i));
	}
	glEnd();
}

void graphic_border(void) {
	glLoadIdentity();
	glLineWidth(1);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(DMAX, DMAX);
	glVertex2d(DMAX, -DMAX);
	glVertex2d(-DMAX, -DMAX);
	glVertex2d(-DMAX, DMAX);
	glEnd();
}


