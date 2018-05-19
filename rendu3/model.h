#ifndef MODEL_H
#define MODEL_H

/**
 * \brief	checks the collisions and prints the associated errors
 */
int initial_collisions(void);

/**
 * \brief	checks the collisions between all the robots, returns 1 if there is at
 * 			least one collision, the arguments stored in pointers are for the first
 * 			collision detected
 * \param	p_dist		pointer for the distance between the two colliding robots
 * \param	p_id_a		pointer for the uniq id of one robot colliding
 * \param	p_id_b		pointer for the uniq id of the other robot colliding
 */
static int robot_collision(	double * p_dist, unsigned int * p_id_a,
							unsigned int * p_id_b);


/**
 * \brief	checks the collisions between all the particles, returns 1 if there is at
 * 			least one collision, the arguments stored in pointers are for the first
 * 			collision detected
 * \param	p_dist		pointer for the distance between the two colliding particles
 * \param	p_id_a		pointer for the uniq id of one particle colliding
 * \param	p_id_b		pointer for the uniq id of the other particle colliding
 */
static int particle_collision(	double * p_dist, unsigned int * p_id_a, 
								unsigned int * p_id_b);


/**
 * \brief	checks the collision between all the robots and all the particles,
 * 			returns 1 if there is at least one collision the arguments stored in 
 * 			pointers are for the first collision detected
 * \param	p_dist		pointer for the distance between the two colliding objects
 * \param	p_id_a		pointer for the uniq id of the particle colliding
 * \param	p_id_b		pointer for the uniq id of the robot colliding
 */
static int cross_collision(	double * p_dist, unsigned int * p_id_a, 
							unsigned int * p_id_b);
static void target_all(double x, double y);
void update(void);
#endif
