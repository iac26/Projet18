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
 * \brief	print the attributes of every particle
 */
void particle_print(void);

/**
 * \brief	returns one particle, the first one selected by
 * 			particle_get_init* the next ones sequentially
 * \param	e		pointer to store the energy of the particle
 * \param	rad		pointer to store the radius of the particle
 * \param	x		pointer to store the x position of the particle
 * \param	y		pointer to store the y position of the particle
 * \param	i_id	pointer to store the iter ID of the particle
 * \param	u_id	pointer to store the uniq ID of the particle
 */
void particle_get(	double * e, double * rad, double * x, double * y,
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
 * \brief	create a particle and returns its uniq ID
 * \param	e		energy of the particle
 * \param	r		radius of the particle
 * \param	x		x position of the particle
 * \param	y		y position of the particle
 */
unsigned int particle_create(double e, double r, double x, double y);

void particle_push_last(void);
void particle_pop_last(void);
void particle_allow_increment(void);
void particle_block_increment(void);

/**
 * \brief	returns the number of particles
 */
int particle_get_nb(void);
void maj_e(void);
double taux(void);
double somme_energy(void);

#endif
