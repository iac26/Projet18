#include <stdio.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "robot.h"
#include "constantes.h"
 
static ROBOT * head = NULL; 
static unsigned int robot_count = 0;
static unsigned int robot_count_u = 0;

struct robot{
	C2D body;
	double angle;
	unsigned int u_id;
	unsigned int i_id;
	ROBOT * next;
};
 
unsigned int robot_create(double x, double y, double a) {
	ROBOT * r = malloc(sizeof(ROBOT));
	if(r) {
		robot_count_u++;
		r->body.centre.x = x;
		r->body.centre.y = y;
		r->body.rayon = R_ROBOT;
		r->angle = a;
		r->i_id = robot_count;
		r->u_id = robot_count_u;
		r->next = head;
		head = r; 
		robot_count++;
	}
	return robot_count_u;
}

void robot_print(void) {
	ROBOT * p = head;
	printf("ROBOTS\n");
	while(p) {
		printf("robot: %u, %u, %lf %lf %lf\n", p->i_id, p->u_id, p->body.centre.x, p->body.centre.y, p->angle);
		ROBOT * tmp = p;
		p = tmp->next;
	}
}

int robot_delete_i(unsigned int id) {
	if(head->i_id == id) {
		ROBOT * tmp = head->next;
		free(head);
		head = tmp;
		robot_count--;
		return 1;
	}
	head->i_id -= 1;
	ROBOT * p = head->next;
	ROBOT * prev = head;
	while(p) {
		if(p->i_id == id) {
			prev->next = p->next;
			free(p);
			robot_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	return 0;
}

int robot_delete_u(unsigned int id) {
	if(head->u_id == id) {
		ROBOT * tmp = head->next;
		free(head);
		head = tmp;
		robot_count--;
		return 1;
	}
	head->i_id -= 1;
	ROBOT * p = head->next;
	ROBOT * prev = head;
	while(p) {
		if(p->u_id == id) {
			prev->next = p->next;
			free(p);
			robot_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	return 0;
}


