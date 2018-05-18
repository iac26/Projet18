/**
 * \file 	graphic.c
 * \brief 	handle everything linked to glut and opengl graphics
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
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
#define POSX 200
#define POSY 200
#define THICK 1.5
#define NORMAL 1.0
#define NEG_QUART_PI 7/4
#ifdef __APPLE__
#define TIME 100
#else
#define TIME 20
#endif
#define TO_DEG 180/M_PI

#define COLOR_LIGHT_BLUE 	0.5f, 0.5f, 1.0f
#define COLOR_LIGHT_GREEN 	0.5f, 1.0f, 0.5f
#define COLOR_DARK_BLUE 	0.0f, 0.0f, 0.5f
#define COLOR_BLACK 		0.0f, 0.0f, 0.0f
#define COLOR_VOMIT_GREEN 	0.6f, 0.7f, 0.6f
#define COLOR_LIGHT_GRAY 	0.2f, 0.2f, 0.2f
#define COLOR_GRAY 			0.5f, 0.5f, 0.5f
#define COLOR_GREEN			0.0f, 1.0f, 0.0f
#define COLOR_YELLOW		1.0f, 1.0f, 0.0f
#define COLOR_WHITE			1.0f, 1.0f, 1.0f
#define COLOR_BLACK			0.0f, 0.0f, 0.0f


static double ratio;
static int width = 800;
static int height = 800;
static double world_width = DMAX;
static double world_height  = DMAX;
static unsigned p = 0, o = 0, i = 0;


int graphic_init_glut(int * argc, char ** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(POSX, POSY);
	glutInitWindowSize(WIDTH,HEIGHT);
	int g_window = glutCreateWindow("ROBOTS");
	glViewport(0, 0, WIDTH, HEIGHT);
	glOrtho(-DMAX, DMAX, -DMAX, DMAX, -1, 1);
	glClearColor(COLOR_WHITE, 1.0);
	return g_window;
}

void graphic_affichage_start(void){
	if(p) {
		glClearColor(COLOR_BLACK, 1.0);
	} else {
		glClearColor(COLOR_WHITE, 1.0);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	graphic_border();
	i++;
	if(!(i%TIME)) {
		o = !o;
	}
}

void graphic_affichage_end(void) {
	glutSwapBuffers();
}

void graphic_reshape(int w, int h){
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	if(h == 0)
		h = 1;
	ratio = (double) w / (double) h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(ratio >= 1.) {
		world_height = DMAX;
		world_width = DMAX*ratio;
	}
	if(ratio < 1.) {
		world_height = DMAX/ratio;
		world_width = DMAX;
	}
	glOrtho(-world_width, world_width, -world_height, world_height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void graphic_robot(double x, double y, double angle, int selected){
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glRotated(angle*TO_DEG, 0.0, 0.0, 1.0);
	if(selected) {
		glColor3f(COLOR_LIGHT_GREEN);
	} else if(p) {
		glColor3f(COLOR_YELLOW);
	} else {
		glColor3f(COLOR_LIGHT_BLUE);
	}
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0.0, 0.0);
	if(p&&o) {
		glVertex2d(0.0, 0.0);
	} else {
		glVertex2d(R_ROBOT, 0.0);
	}
	for(double i = M_PI/4; i <= M_PI*NEG_QUART_PI; i += 2*M_PI/R_RES){
		glVertex2d(R_ROBOT*cos(i), R_ROBOT*sin(i));
	}
	if(p&&o) {
		glVertex2d(0.0, 0.0);
	} else {
		glVertex2d(R_ROBOT, 0.0);
	}
	glEnd();
	glColor3f(COLOR_DARK_BLUE);
	if(!p){
		glBegin(GL_LINE_LOOP);
		for(double i = M_PI/4; i < M_PI*NEG_QUART_PI; i += 2*M_PI/R_RES){
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
}

void graphic_particle(double r, double x, double y){
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	if(p) {
		glColor3f(COLOR_GREEN);
	} else {
		glColor3f(COLOR_VOMIT_GREEN);
	}
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

void graphic_debug(double ra, double x, double y, float r, float g, float b){
	glLoadIdentity();
	glTranslated(x, y, 0.0);
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	for(double i = 0; i < 2.0*M_PI; i += 2*M_PI/R_RES){
		glVertex2d(ra*cos(i), ra*sin(i));
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

void graphic_toggle_p(void) {
	p = !p;
}

void graphic_convert_mouse(double * x, double * y) {
	*x = ((*x - (double)width/2)/((double)width/2))*world_width;
	*y = height - *y;
	*y = ((*y - (double)height/2)/((double)height/2))*world_height;
}




