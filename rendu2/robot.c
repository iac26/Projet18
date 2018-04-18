#include <stdio.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "robot.h"
#include "constantes.h"
 
static ROBOT * head = NULL; 
static ROBOT * last = NULL;
static unsigned int robot_count = 0;
static unsigned int robot_count_u = 0;

struct robot{
	C2D body;
	double angle;
	unsigned int u_id;
	unsigned int i_id;
	ROBOT * next;
};
 
unsigned int robot_create(double x, double y, double a){
	ROBOT * r = malloc(sizeof(ROBOT));
	if(r){
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

void robot_print(void){
	ROBOT * p = head;
	printf("ROBOTS\n");
	while(p){
		printf("robot: %u, %u, %lf %lf %lf\n", p->i_id, p->u_id, p->body.centre.x, p->body.centre.y, p->angle);
		p = p->next;
	}
}

int robot_delete_i(unsigned int id){
	if(head->i_id == id){
		ROBOT * tmp = head->next;
		free(head);
		head = tmp;
		robot_count--;
		return 1;
	}
	head->i_id -= 1;
	ROBOT * p = head->next;
	ROBOT * prev = head;
	while(p){
		if(p->i_id == id){
			prev->next = p->next;
			free(p);
			robot_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	p = head;
	while(p){
		p->i_id += 1;
		p = p->next;
	}
	return 0;
}

void robot_delete_all(void){
	ROBOT * r = head;
	head = NULL;
	robot_count = 0;
	robot_count_u = 0;
	ROBOT * tmp = NULL;
	while(r){
		tmp = r->next;
		free(r);
		r = tmp;
	}
	//if(r)
	//	free(r);
}

int robot_delete_u(unsigned int id){
	if(head->u_id == id){
		ROBOT * tmp = head->next;
		free(head);
		head = tmp;
		robot_count--;
		return 1;
	}
	head->i_id -= 1;
	ROBOT * p = head->next;
	ROBOT * prev = head;
	while(p){
		if(p->u_id == id){
			prev->next = p->next;
			free(p);
			robot_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	p = head;
	while(p){
		p->i_id += 1;
		p = p->next;
	}
	return 0;
}

void robot_get_init_i(unsigned int id){
	ROBOT * p = head;
	last = head;
	while(p){
		if(p->i_id == id){
			last = p;
			break;
		}
		p = p->next;
	}
}

void robot_get_init_u(unsigned int id){
	ROBOT * p = head;
	last = head;
	while(p){
		if(p->u_id == id){
			last = p;
			break;
		}
		p = p->next;
	}
}

int robot_get_nb(void){
	return robot_count;
}

void robot_get(double * x, double * y, double * angle, unsigned int * i_id, unsigned int * u_id){
	if(x)
		*x = last->body.centre.x;
	if(y)
		*y = last->body.centre.y;
	if(angle)
		*angle = last->angle;
	if(i_id)
		*i_id = last->i_id;
	if(u_id)
		*u_id = last->u_id;
	if(last)
		last = last->next;
}


