/**
 * \file 	robot.c
 * \brief 	robot storage and misc tasks
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utilitaire.h"
#include "robot.h"
#include "constantes.h"

#define STACK_SIZE 10
 
static ROBOT * head = NULL; 
static ROBOT * last = NULL;
static unsigned int stack_pointer = 0;
static ROBOT * stack[STACK_SIZE];
static unsigned int robot_count = 0;
static unsigned int robot_count_u = 0;
static unsigned short increment = 1;

struct robot{
	C2D body;
	S2D prev_pos;
	S2D quad;
	S2D target;
	double angle;
	int selected;
	int blocked;
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
		r->selected = 0;
		r->blocked = 0;
		r->i_id = robot_count;
		r->u_id = robot_count_u;
		r->next = head;
		head = r; 
		robot_count++;
	}
	//printf("created\n");
	return robot_count_u;
}

void robot_print(void){
	ROBOT * p = head;
	printf("ROBOTS\n");
	while(p){
		printf("robot: %u, %u, %lf %lf %lf\n", 	p->i_id, p->u_id, 
												p->body.centre.x, p->body.centre.y, 
												p->angle);
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

void robot_get_init_head(void) {
	last = head;
}

int robot_get_nb(void){
	return robot_count;
}

void robot_unblock(void) {
	if(last) {
		last->blocked = 0;
		if(increment)
			last = last->next;
	}
}


int robot_get_blocked(void) {
	if(last) {
		int blocked = last->blocked;
		if(increment)
			last = last->next;
		return blocked;
	}
	return 0;
}

void robot_allow_increment(void) {
	increment = 1;
}

void robot_increment(void) {
	last = last->next;
}

void robot_block_increment(void) {
	increment = 0;
}

void robot_push_last(void) {
	if(stack_pointer > STACK_SIZE) {
		#ifdef DEBUG
		printf("robot stack overflow\n");
		#endif
	} else {
		stack[stack_pointer] = last;
		stack_pointer++;
	}
}

void robot_pop_last(void) {
	if(stack_pointer <= 0) {
		#ifdef DEBUG
		printf("robot stack underflow\n");
		#endif
	} else {
		stack_pointer--;
		last = stack[stack_pointer];
	}
}

void robot_move(double dist, double angle) {
	if(last) {
		last->prev_pos = last->body.centre;
		last->body.centre = util_deplacement(last->body.centre, last->angle, dist);
		last->angle = last->angle + angle;
		util_range_angle(&(last->angle));
		if(	fabs(last->prev_pos.x - last->body.centre.x) < EPSIL_ZERO &&
			fabs(last->prev_pos.y - last->body.centre.y) < EPSIL_ZERO &&
			!(	last->target.x == last->body.centre.x &&
				last->target.y == last->body.centre.y)) {
			if(	fabs(angle) < EPSIL_ZERO) {
				last->blocked++;
			}
		} else {
			last->blocked = 0;
		}
		if(increment)
			last = last->next;
	}
}

void robot_set_target(S2D target) {
	if(last) {
		last->target = target;
		if(increment)
			last = last->next;
	}
}

void robot_set_all_targets(S2D target) {
	ROBOT * p = head;
	while(p){
		p->target = target;
		p = p->next;
	}
} 

void robot_randomize_targets(void) {
	ROBOT * p = head;
	while(p){
		S2D target = {(double) rand()/RAND_MAX, (double) rand()/RAND_MAX};
		p->target = target;
		p = p->next;
	}
}

void robot_select(void){
	if(last) {
		last->selected = 1;
		#ifdef DEBUG
		double e_angle;
		util_ecart_angle(last->body.centre, last->angle, last->target, &e_angle);
		printf(	"ROBOT INFO %d:\n"
				"ANGLE:		%lf\n"
				"POS: 		%lf %lf\n"
				"TARGET:	%lf %lf (%lf)\n"
				"BLOCKED: %d\n", last->u_id, last->angle,
				last->body.centre.x, last->body.centre.y,
				last->target.x, last->target.y, e_angle, last->blocked);
		#endif
		if(increment) {
			last = last->next;
		}
	}
}

void robot_deselect(void){
	if(last) {
		last->selected = 0;
		if(increment) {
			last = last->next;
		}
	}
}

void robot_deselect_all(void){
	ROBOT * p = head;
	last = head;
	while(p){
		p->selected = 0;
		p = p->next;
	}
}

void robot_set_quad(double x, double y) {
	if(last) {
		S2D quad = {x, y};
		last->quad = quad;
		if(increment) {
			last = last->next;
		}
	}
}

void robot_get(	S2D * pos, S2D * quad, S2D * target, double * angle, int * selected,
				unsigned int * i_id, unsigned int * u_id){
	if(last) {
		if(pos)
			*pos = last->body.centre;
		if(quad)
			*quad = last->quad;
		if(target)
			*target = last->target;
		if(angle)
			*angle = last->angle;
		if(selected)
			*selected = last->selected;
		if(i_id)
			*i_id = last->i_id;
		if(u_id)
			*u_id = last->u_id;
		if(increment)
			last = last->next;
	}
}


