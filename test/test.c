/* CUSTOM TEST FILE
 * made for the prog II project (rendu1)
 * by Iacopo Sprenger (3.3.2018)
 * */

#include <stdlib.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

#include "../utilitaire.h"

#define FLEN 10
#define P_SPEED 0.0005
#define PI 3.14159

C2D player, dummy;

void affichage(void);
void keyboard(char key);
void mouse(int button, int state, int x, int y);
void keyboard_2(char key);
void calculs(void);
void correct(void);
void init(C2D* o, double x, double y, double r);
void draw_text(char *string, double x, double y);
void draw_circle(C2D o);
double convert_y(int y);
double convert_x(int x);
void quit(void); 

double vx;
double vy;

double dx;
double dy;

double dist;
double angle;
double e_vert_top;
double e_vert_bottom;
double e_hor_left;
double e_hor_right;
unsigned short collision;
unsigned short vert_top;
unsigned short vert_bottom;
unsigned short hor_left;
unsigned short hor_right;
unsigned short pt_dedans;

unsigned short up;
unsigned short down;
unsigned short left;
unsigned short right;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Test"); 
	init(&player, 1.0, 2.0, 0.2);
	init(&dummy, 2.0, 2.0, 0.2);
	glutDisplayFunc(affichage);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_2);
	glutMouseFunc(mouse);
	glutTimerFunc(FLEN, calculs, 0);
	glutMainLoop();
}

void affichage(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0, 4.0, 0, 4.0, -1, 1);
	char t1[50];
	sprintf(t1, "vx %lf / vy %lf", vx, vy);
	draw_text(t1, 0.1, 3.8);
	char t2[50];
	sprintf(t2, "dist %lf / angle %lf (%.2g PI)", dist, angle, angle/M_PI);
	draw_text(t2, 0.1, 3.6);
	char t3[50];
	sprintf(t3, "collision: %d / centre ds cercl: %d", collision, pt_dedans);
	draw_text(t3, 0.1, 3.4);
	char t4[100];
	sprintf(t4, "top: %d (%lf) / bottom: %d (%lf)", vert_top, e_vert_top, vert_bottom, e_vert_bottom);
	draw_text(t4, 0.1, 3.2);
	char t5[100];
	sprintf(t5, "left: %d (%lf) / right: %d (%lf)", hor_left, e_hor_left, hor_right, e_hor_right);
	draw_text(t5, 0.1, 3.0);
	draw_circle(player);
	draw_circle(dummy);
	
	glutSwapBuffers();
}

void keyboard(char key) {
	switch (key) {
		case 27:
			quit();
			break;
		case 'w':
			up = 1;
			break;
		case 's':
			down = 1;
			break;
		case 'a':
			left = 1;
			break;
		case 'd':
			right = 1;
			break;
		case ' ':
			vx = 0.0;
			vy = 0.0;
			break;
	}
}

void keyboard_2(char key) {
	switch(key) {
		case 'w':
			up = 0;
			break;
		case 's':
			down = 0;
			break;
		case 'a':
			left = 0;
			break;
		case 'd':
			right = 0;
			break;
		}
}

void mouse(int button, int state, int x, int y) {
	if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN)) {
		dx = convert_x(x) - player.centre.x;
		dy = convert_y(y) - player.centre.y;
		vx = 0.0;
		vy = 0.0;
		correct();
	}
}

double convert_x(int x) {
	return ((double) x / 400)*4.0;
}

double convert_y(int y) {
	y -= 400; 
	y *= -1;
	return ((double) y / 400)*4.0;
}

void calculs(void) {
	if(up) {
		vy += P_SPEED;
	}
	if(down) {
		vy -= P_SPEED;
	}
	if(left) {
		vx -= P_SPEED;
	}
	if(right) {
		vx += P_SPEED;
	}
	angle = util_angle(player.centre, dummy.centre);
	dist = util_distance(player.centre, dummy.centre);
	collision = util_collision_cercle(player, dummy, NULL);
	pt_dedans = util_point_dans_cercle(player.centre, dummy);
	
	vert_top = util_alignement(player.centre, 0.5*M_PI, dummy.centre);
	util_ecart_angle(player.centre, 0.5*M_PI, dummy.centre, &e_vert_top);
	
	hor_right = util_alignement(player.centre, 0.0, dummy.centre);
	util_ecart_angle(player.centre, 0.0, dummy.centre, &e_hor_right);
	
	vert_bottom = util_alignement(player.centre, -0.5*M_PI, dummy.centre);
	util_ecart_angle(player.centre, -0.5*M_PI, dummy.centre, &e_vert_bottom);
	
	hor_left = util_alignement(player.centre, M_PI, dummy.centre);
	util_ecart_angle(player.centre, M_PI, dummy.centre, &e_hor_left);
	
	
	player.centre.x += vx;
	player.centre.y += vy;
	
	
	
	glutPostRedisplay();
	glutTimerFunc(FLEN, calculs, 0);
}

void correct(void) {
	double dist;
	double n_delta_d;
	double o_x = player.centre.x;
	double o_y = player.centre.y;
	double do_x = o_x - dummy.centre.x;
	double do_y = o_y - dummy.centre.y;
	double L = sqrt(do_x*do_x + do_y*do_y);
	printf("cfmove %lf %lf\n", dx, dy);
	player.centre.x += dx;
	player.centre.y += dy;
	double delta_d = sqrt(dx*dx + dy*dy);
	if(util_collision_cercle(player, dummy, &dist)) {
		if(!util_inner_triangle(delta_d, dist, L, player.rayon+dummy.rayon, &n_delta_d)) {
			printf("someissue\n");
		}
		dx *= (n_delta_d/delta_d);
		dy *= (n_delta_d/delta_d);
		player.centre.x = o_x + dx;
		player.centre.y = o_y + dy;
		printf("delta_d: %lf n_delta_d: %lf\n", delta_d, n_delta_d);
		printf("corrected %lf %lf\n", dx, dy);
	}
	
}

void draw_circle(C2D o) {
	glPushMatrix();
	glTranslated(o.centre.x, o.centre.y, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		for(double i = 0.0; i < 2*M_PI; i += (2*M_PI/24)) {
			glVertex2d(o.rayon*sin(i), o.rayon*cos(i));
		}
	glEnd();
	glLoadIdentity();
	glPopMatrix();
}

void init(C2D* o, double x, double y, double r) {
	o->centre.x = x;
	o->centre.y = y;
	o->rayon = r;
}

void draw_text(char *string, double x, double y) {  
	char *c;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2d(x, y);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}

void quit(void) {
	glutDestroyWindow(1);
	exit(0);
}
