/**
 * \file 	particle.c
 * \brief 	particle storage and misc tasks
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
 */
#include <stdio.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "particle.h"
#include "constantes.h"
 
static PARTICLE * head = NULL; 
static PARTICLE * last = NULL;
static PARTICLE * tmp_last = NULL;
static unsigned int particle_count = 0;
static unsigned int particle_count_u = 0;
static unsigned short increment = 1;
static unsigned short event = 1;
static unsigned short end_decomp = 0;
static double total_energy = 0;
static double elim_energy = 0;

struct particle{
	C2D body;
	double energy;
	int targeted:1;
	unsigned int u_id;
	unsigned int i_id;
	PARTICLE * next;
};
 
unsigned int particle_create(double e, double r, double x, double y){
	PARTICLE * p = malloc(sizeof(PARTICLE));
	PARTICLE * this = head;
	PARTICLE * prev = NULL;
	if(p){
		while(this) {
			if(r > this->body.rayon){
				particle_count_u++;
				p->body.centre.x = x;
				p->body.centre.y = y;
				p->body.rayon = r;
				p->energy = e;
				p->next = this;
				if(!prev){
					head = p;
					p->i_id = particle_count;
				}else{
					prev->next = p;
					p->i_id = prev->i_id-1;
				}
				p->u_id = particle_count_u;
				particle_count++;
				total_energy += e;
				return particle_count_u;
			}
			this->i_id++;
			prev = this;
			this = this->next;
		}
		particle_count_u++;
		p->body.centre.x = x;
		p->body.centre.y = y;
		p->body.rayon = r;
		p->energy = e;
		p->next = NULL;
		if(!prev){
			head = p;
		}else{
			prev->next = p;
		}
		p->i_id = 0;
		p->u_id = particle_count_u;
		particle_count++;
		total_energy += e;
		return particle_count_u;
	}
	return 0;
}

void particle_print(void){
	PARTICLE * p = head;
	printf("PARTICLES\n");
	while(p){
		printf("particule: %u, %u, %lf %lf %lf %lf\n",	p->i_id, p->u_id, p->energy,
														p->body.rayon, 
														p->body.centre.x, 
														p->body.centre.y);
		PARTICLE * tmp = p;
		p = tmp->next;
	}
}

int particle_delete_i(unsigned int id){
	event = 1;
	if(head->i_id == id){
		PARTICLE * tmp = head->next;
		elim_energy += head->energy;
		free(head);
		head = tmp;
		particle_count--;
		return 1;
	}
	head->i_id -= 1;
	PARTICLE * p = head->next;
	PARTICLE * prev = head;
	while(p){
		if(p->i_id == id){
			prev->next = p->next;
			elim_energy += p->energy;
			free(p);
			particle_count--;
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

int particle_delete_u(unsigned int id){
	event = 1;
	if(head->u_id == id){
		PARTICLE * tmp = head->next;
		elim_energy += head->energy;
		free(head);
		head = tmp;
		particle_count--;
		return 1;
	}
	head->i_id -= 1;
	PARTICLE * p = head->next;
	PARTICLE * prev = head;
	while(p){
		if(p->u_id == id){
			prev->next = p->next;
			elim_energy += p->energy;
			free(p);
			particle_count--;
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

void particle_delete_all(void){
	PARTICLE * p = head;
	PARTICLE * tmp;
	head = NULL;
	particle_count = 0;
	particle_count_u = 0;
	elim_energy = 0;
	total_energy = 0;
	end_decomp = 0;
	event = 1;
	while(p){
		tmp = p->next;
		free(p);
		p = tmp;
	}
	if(p)
		free(p);
}

int particle_get_nb(void){
	return particle_count;
} 

void particle_get_init_head(void){
	last = head;
} 

void particle_get_init_i(unsigned int id){
	PARTICLE * p = head;
	last = head;
	while(p){
		if(p->i_id == id){
			last = p;
			break;
		}
		p = p->next;
	}
}

void particle_get_init_u(unsigned int id){
	PARTICLE * p = head;
	last = head;
	while(p){
		if(p->u_id == id){
			last = p;
			break;
		}
		p = p->next;
	}
}

void particle_push_last(void){
	tmp_last = last;
}

void particle_pop_last(void){
	last = tmp_last;
}

void particle_target(void){
	if(last){
		last->targeted = 1;
		if(increment)
			last = last->next;
	}
}

void particle_untarget(void){
	if(last){
		last->targeted = 0;
		if(increment)
			last = last->next;
	}
}

void particle_untarget_all(void){
	PARTICLE * p = head;
	while(p){
		p->targeted = 0;
		p = p->next;
	}
}

int particle_targeted(void){
	if(last){
		return last->targeted;
	}
	return 1;
}

void particle_allow_increment(void){
	increment = 1;
}

void particle_block_increment(void){
	increment = 0;
}

void particle_increment(void){
	if(last){
		last = last->next;
	}
}

int particle_finished(void){
	if(head){
		return 0;
	}
	return 1;
}

void particle_decomposition(void){
	PARTICLE * p = head;
	double new_r, new_e;
	end_decomp = 1;
	while(p){
		if(p->body.rayon > R_PARTICULE_MIN/R_PARTICULE_FACTOR){
			end_decomp = 0;
		}
		if((double)rand()/RAND_MAX < DECOMPOSITION_RATE){
			new_r = p->body.rayon * R_PARTICULE_FACTOR;
			new_e = p->energy * E_PARTICULE_FACTOR;
			if(new_r >= R_PARTICULE_MIN){
				event = 1;
				double x = p->body.centre.x;
				double y = p->body.centre.y;
				particle_create(new_e, new_r, x + new_r, y + new_r); 
				particle_create(new_e, new_r, x - new_r, y + new_r); 
				particle_create(new_e, new_r, x + new_r, y - new_r); 
				particle_create(new_e, new_r, x - new_r, y - new_r); 
				particle_delete_u(p->u_id);
			}
		}
		p = p->next;
	}
}

double particle_get_tot_energy(void){
	return total_energy;
}

double particle_get_elim_energy(void){
	return elim_energy;
}

unsigned short particle_get_event(void){
	unsigned short tmp = event;
	event = 0;
	return tmp;
}

void particle_get(	double * e, C2D * body,
					unsigned int * i_id, unsigned int * u_id){
	if(last){
		if(body)
			*body = last->body;
		if(e)
			*e = last->energy;
		if(i_id)
			*i_id = last->i_id;
		if(u_id)
			*u_id = last->u_id;
		if(increment)
			last = last->next; 
	}
}

unsigned short particle_decomp_finished(void){
	return end_decomp;
}


