#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utilitaire.h"
#include "robot.h"
#include "constantes.h"
 
static ROBOT * head = NULL; 
static unsigned int robot_count = 0; 
 
struct robot{
	C2D body;
	double angle;
	unsigned int id;
	ROBOT * next;
};
 
unsigned int robot_create(double x, double y, double a) {
	ROBOT * r = malloc(sizeof(ROBOT));
	if(r) {
		robot_count++;
		r->body.centre.x = x;
		r->body.centre.y = y;
		r->body.rayon = R_ROBOT;
		r->angle = a;
		r->id = robot_count;
		r->next = head;
		head = r; 
	}
	return robot_count;
}

void robot_print(void) {
	ROBOT * p = head;
	while(p) {
		printf("robot: %u, %lf %lf %lf\n", p->id, p->body.centre.x, p->body.centre.y, p->angle);
		ROBOT * tmp = p;
		p = tmp->next;
	}
}

int robot_delete(unsigned int id) {
	if(head->id == id) {
		ROBOT * tmp = head->next;
		free(head);
		head = tmp;
		return 1;
	}
	head->id -= 1;
	ROBOT * p = head->next;
	ROBOT * prev = head;
	while(p) {
		if(p->id == id) {
			prev->next = p->next;
			free(p);
			return 1;
		}
		p->id -= 1;
		prev = p;
		p = prev->next;
	}
	return 0;
}




