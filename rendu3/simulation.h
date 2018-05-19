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

/**
 * \brief	collisions for one robot against the other robots and all the particles
 * 			this function also handles the movement correction and the particle eating
 * 			returns 1 if a particle has been eaten
 * \param	_this		//NOT FINISHED !!!
 */							
static int single_collisions(	C2D _this, double angle, double tran, double rot, 
								unsigned int u_id);				
/**
 * \brief	update all robots's positions and particles's data.
 */
void simulation_update(void);

/**
 * \brief	select the robot which is pointing by the pointer "point".
 * \param	point		pointer which indicate th position of the mouse.
 */
void simulation_select(S2D point);

/**
 * \brief	this function chooses the ideal target for every robots.
 */
void simulation_select_targets(void);

/**
 * \brief	this function changes the last robot's target, the closest one.
 */
void simulation_handle_blocked(void);

/**
 *  \brief deletes every robots and particles
 */
void simulation_init(void);

/**
 *  \brief turns manual control on, changing manual control's variable to 1.
 * 
 */
void simulation_set_manual_control(void);

/**
 * \brief turns manual control off, deselect every robots
 */	
void simulation_set_auto_control(void);

/**
 * \brief	returns the value of control mode(on or off).
 */	
int simulation_get_control_mode(void);

/**
 * \brief	accelerates the robot while a manual control mode.
*/
void simulation_man_for(void);

/**
 * \brief	slows down the robot while a manual control mode.
 */	
void simulation_man_back(void);

/**
 * \brief	gives a velocity to the robot to turn left while a manual control mode
 */	
void simulation_man_left(void);

/**
 * \brief	gives a velocity to the robot to turn right while a manual control mode
 */	
void simulation_man_right(void);

/**
 * \brief	returns the value of selected robot's transition velocity.
 */
double simulation_get_man_vtran(void);

/**
 * \brief	returns the value of selected robot's rotation velocity.
 */
double simulation_get_man_vrot(void);

/**
 * \brief	returns the value of selected robot's Vtran.
 */
void simulation_reset_man(void);

/**
 * \brief	returns the pourcentage of the energy rate
 */
double simulation_get_rate(void);

/**
 * \brief	indicates if simulation is finished(return 1), else returns 0.
 */
int simulation_get_finished(void);

/**
 * \brief	prints every robots and particles.
 */
void simulation_print_everything(void);

/**
 * \brief	assign robots their quads respecting same number of robots per quads.
 */
void simulation_assign_quads(void);

/**
 * \brief	returns 1 if there is no collision between every elements of 
 * 			the simulation. else return 0 and print error message.
 */
int simulation_initial_collisions();
#endif
