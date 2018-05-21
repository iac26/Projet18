/**
 * \file 	particle.h
 * \brief 	particle storage and misc tasks
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
 */
#ifndef PARTICLE_H
#define PARTICLE_H

/*
 * every particle has the following attributes:
 * body			position and radius
 * energy		energy
 * u_id			unique identifier
 * i_id			iteration identifier
 * next			link to the previous particle
 * */
 #include "utilitaire.h"
 
typedef struct particle PARTICLE;

/**
 * \brief	delete one particle selected by its unique ID
 * \param	id		the unique ID of the particle to delete
 */
int particle_delete_u(unsigned int id);

/**
 * \brief	delete one particle selected by its iteration ID
 * \param	id		the iteration ID of the particle to delete
 */
int particle_delete_i(unsigned int id);

/**
 * \brief	delete every particle
 */
void particle_delete_all(void);

/**
 * \brief	handles decompositions for every particle
 */
void particle_decomposition(void);

/**
 * \brief	print the attributes of every particle
 */
void particle_print(void);

/**
 * \brief	stores in pointers the data from current particle
 * \param	e		pointer to store the energy of the particle
 * \param	rad		pointer to store the radius of the particle
 * \param	x		pointer to store the x position of the particle
 * \param	y		pointer to store the y position of the particle
 * \param	i_id	pointer to store the iter ID of the particle
 * \param	u_id	pointer to store the uniq ID of the particle
 */
void particle_get(	double * e, C2D * body,
					unsigned int * i_id, unsigned int * u_id);

/**
 * \brief	initialize the get function to a particle (iter ID)
 * \param	id		the iteration ID of the next particle to get
 */
void particle_get_init_i(unsigned int id);

/**
 * \brief	initialize the get function to a particle (uniq ID)
 * \param	id		the unique ID of the next particle to get
 */
void particle_get_init_u(unsigned int id);

/**
 * \brief	initialize the get function to the head of the list
 */
void particle_get_init_head(void);

/**
 * \brief	create a particle and returns its uniq ID and orders the list
 * \param	e		energy of the particle
 * \param	r		radius of the particle
 * \param	x		x position of the particle
 * \param	y		y position of the particle
 */
unsigned int particle_create(double e, double r, double x, double y);

/**
 * \brief	stores a copy of the selection context
 */
void particle_push_last(void);

/**
 * \brief	pops back a stored copy of the selection context
 */
void particle_pop_last(void);

/**
 * \brief	allows automatic selection of the next particle
 */
void particle_allow_increment(void);

/**
 * \brief	blocks automatic selection of the next particle
 */
void particle_block_increment(void);

/**
 * \brief	manual selection of the next particle
 */
void particle_increment(void);

/**
 * \brief	returns the summed energy of all created particles
 */
double particle_get_tot_energy(void);

/**
 * \brief	returns the summed energy of all deleted particles
 */
double particle_get_elim_energy(void);

/**
 * \brief	untargets every particle
 */
void particle_untarget_all(void);

/**
 * \brief	targets the current particle
 */
void particle_target(void);

/**
 * \brief	untargets the current particle
 */
void particle_untarget(void);

/**
 * \brief	returns 1 if the current particle is targeted
 */
int particle_targeted(void);

/**
 * \brief	returns 1 no particles are left
 */
int particle_finished(void);

/**
 * \brief	returns 1 if a particle was deleted since the last call of this function
 */
unsigned short particle_get_event(void);

/**
 * \brief	returns 1 if decomposition cannot happen anymore
 */
unsigned short particle_decomp_finished(void);

/**
 * \brief	returns the number of particles
 */
int particle_get_nb(void);


#endif
