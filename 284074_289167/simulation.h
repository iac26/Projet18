/**
 * \file 	simulation.h
 * \brief 	handles the simulation
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
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
 * \param	_this		the robots current position
 * \param	angle 		the robots current angle
 * \param	tran		the robots planned translation
 * \param	rot			the robots planned rotation
 * \param	u_id		the robots unique ID
 */					
static int single_collisions(	C2D _this, double angle, double tran, double rot, 
								unsigned int u_id);		
										
/**
 * \brief	collisions for one robot against one particles
 * \param	_this		the robots current position
 * \param	new_this	the robots planned position
 * \param	angle 		the robots current angle
 * \param	tran		pointer to store the new translation
 * \param	eaten		pointer to store the unique ID of the eaten particle
 */	
static int single_collisions_particle(	C2D _this, C2D new_this, double angle, 
										double * tran, int * eaten);
										
/**
 * \brief	collisions for one robot against another robot
 * \param	_this		the robots current position
 * \param	new_this	the robots planned position
 * \param	tran		pointer to store the new translation
 * \param	u_id		the robots unique ID
 */											
static int single_collisions_robot(	C2D _this, C2D new_this, double * tran,
									unsigned u_id);
/**
 * \brief	
 */				
static void simulation_move(void);

/**
 * \brief	selects the clicked robot
 * \param	point	mouse click position
 */	
void simulation_select(S2D point);

/**
 * \param	target assignement for when particles are still decomposing
 */
static void select_in_quads(void);

/**
 * \param	target assignement for when all particles are done decomposing
 */
static void select_decomp_finished(void);

/**
 * \param	assign a target to each non-blocked robot
 */
static void simulation_select_targets(void);

/**
 * \brief	assign a target to every blocked robot
 */	
static void simulation_handle_blocked(void);

/**
 * \brief	assign a quadrant to each robot (if nb robot >= 4)
 */	
static void simulation_assign_quads(void);

/**
 * \brief	the simulation main function. Called every step
 */										
void simulation_update(void);

/**
 * \brief	initialize the simulation
 */	
void simulation_init(void);

/**
 * \brief	enable manual control
 */	
void simulation_set_manual_control(void);

/**
 * \brief	disable manual control
 */	
void simulation_set_auto_control(void);

/**
 * \brief	return the control mode
 */	
int simulation_get_control_mode(void);

/**
 * \brief	increase manual vtran
 */	
void simulation_man_for(void);

/**
 * \brief	decrease manual vtran
 */	
void simulation_man_back(void);

/**
 * \brief	increase manual vrot
 */	
void simulation_man_left(void);

/**
 * \brief	decrease manual vrot
 */	
void simulation_man_right(void);

/**
 * \brief	return manual vtran
 */
double simulation_get_man_vtran(void);

/**
 * \brief	return manual vrot
 */
double simulation_get_man_vrot(void);

/**
 * \brief	reset manual vtran and vrot
 */
void simulation_reset_man(void);

/**
 * \brief	return the decomposition rate
 */
double simulation_get_rate(void);

/**
 * \brief	return 1 if all particles have been eaten
 */
int simulation_get_finished(void);

/**
 * \brief	calls graphic to draw the screen
 */
void simulation_print_everything(void);

#endif
