/**
 * \file 	simulation.h
 * \brief 	handles the simulation
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#ifndef SIMULATION_H
#define SIMULATION_H
#include "utilitaire.h"

/**
 * \brief	checks the collisions and prints the associated errors
 */
int simulation_initial_collisions(void);

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

/**
 * \brief	collisions for one robot against the other robots and all the particles
 * 			this function also handles the movement correction and the particle eating
 * 			returns 1 if a particle has been eaten
 * \param	_this		*/ //NOT FINISHED !!!						
static int single_collisions(	C2D _this, double angle, double tran, double rot, 
								unsigned int u_id);				

static int single_collisions_particle(	C2D _this, C2D new_this, double angle, 
										double * tran, int * collisions, int * eaten);
										
static int single_collisions_robot(	C2D _this, C2D new_this, double * tran,
										int * collisions, unsigned u_id);
										
void simulation_update(void);
void simulation_select(S2D point);

void simulation_select_targets(void);
void simulation_handle_blocked(void);

void simulation_init(void);

void simulation_set_manual_control(void);
void simulation_set_auto_control(void);
int simulation_get_control_mode(void);
void simulation_man_for(void);
void simulation_man_back(void);
void simulation_man_left(void);
void simulation_man_right(void);
void simulation_assign_quads(void);
double simulation_get_man_vtran(void);
double simulation_get_man_vrot(void);
void simulation_reset_man(void);
double simulation_get_rate(void);
int simulation_get_finished(void);
void simulation_print_everything(void);

#endif
