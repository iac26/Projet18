#include <stdio.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "particle.h"
#include "constantes.h"
 
static PARTICLE * head = NULL; 
static PARTICLE * last = NULL;
static unsigned int particle_count = 0;
static unsigned int particle_count_u = 0;
static int nb_particle = 0;

struct particle{
	C2D body;
	double energy;
	unsigned int u_id;
	unsigned int i_id;
	PARTICLE * next;
};
 
unsigned int particle_create(double e, double r, double x, double y) {
	PARTICLE * p = malloc(sizeof(PARTICLE));
	if(p) {
		particle_count_u++;
		p->body.centre.x = x;
		p->body.centre.y = y;
		p->body.rayon = r;
		p->energy = e;
		p->i_id = particle_count;
		p->u_id = particle_count_u;
		p->next = head;
		head = p; 
		particle_count++;
	}
	return particle_count_u;
}

void particle_print(void) {
	PARTICLE * p = head;
	printf("PARTICLES\n");
	while(p) {
		printf("particule: %u, %u, %lf %lf %lf %lf\n", p->i_id, p->u_id, p->energy, p->body.rayon, p->body.centre.x, p->body.centre.y);
		PARTICLE * tmp = p;
		p = tmp->next;
	}
}

int particle_delete_i(unsigned int id) {
	if(head->i_id == id) {
		PARTICLE * tmp = head->next;
		free(head);
		head = tmp;
		particle_count--;
		return 1;
	}
	head->i_id -= 1;
	PARTICLE * p = head->next;
	PARTICLE * prev = head;
	while(p) {
		if(p->i_id == id) {
			prev->next = p->next;
			free(p);
			particle_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	return 0;
}

int particle_delete_u(unsigned int id) {
	if(head->u_id == id) {
		PARTICLE * tmp = head->next;
		free(head);
		head = tmp;
		particle_count--;
		return 1;
	}
	head->i_id -= 1;
	PARTICLE * p = head->next;
	PARTICLE * prev = head;
	while(p) {
		if(p->u_id == id) {
			prev->next = p->next;
			free(p);
			particle_count--;
			return 1;
		}
		p->i_id -= 1;
		prev = p;
		p = prev->next;
	}
	return 0;
}

void particle_set_nb(int nb) {
	nb_particle = nb;
}

int particle_get_nb(void) {
	return nb_particle;
} 

void particle_get_init(unsigned int id) {
	PARTICLE * p = head;
	last = head;
	while(p){
		if(p->i_id == id) {
			last = p;
			break;
		}
		p = p->next;
	}
}

void particle_get(double * e, double * rad, double * x, double * y, unsigned int * i_id, unsigned int * u_id) {
	if(x)
		*x = last->body.centre.x;
	if(y)
		*y = last->body.centre.y;
	if(e)
		*e = last->energy;
	if(rad)
		*rad = last->body.rayon;
	if(i_id)
		*i_id = last->i_id;
	if(u_id)
		*u_id = last->u_id;
	if(last)
		last = last->next; 
}


