/**
 * \file 	robot.h
 * \brief 	robot storage and misc tasks
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#ifndef ROBOT_H
#define ROBOT_H

#include "utilitaire.h"

/*
 * every robot has the following attributes:
 * body			position and radius
 * angle		orientation
 * u_id			unique identifier
 * i_id			iteration identifier
 * next			link to the previous robot
 * */

typedef struct robot ROBOT;

/**
 * \brief	delete one robot selected by its unique ID
 * \param	id		the unique ID of the robot to delete
 */
int robot_delete_u(unsigned int id);

/**
 * \brief	delete one robot selected by its iteration ID
 * \param	id		the iteration ID of the robot to delete
 */
int robot_delete_i(unsigned int id);

/**
 * \brief	delete every robot
 */
void robot_delete_all(void);

/**
 * \brief	print the attributes of every robot
 */
void robot_print(void);

/**
 * \brief	initialize the get function to a robot (iter ID)
 * \param	id		the iteration ID of the next robot to get
 */
void robot_get_init_i(unsigned int id);

/**
 * \brief	initialize the get function to a robot (uniq ID)
 * \param	id		the unique ID of the next robot to get
 */
void robot_get_init_u(unsigned int id);

/**
 * \brief	initialize the get function to the head of the list
 */
void robot_get_init_head(void);

/**
 * \brief	set the target of the selected robot
 * \param 	target		target for the robot
 */
void robot_set_target(S2D target);

/**
 * \brief	set a random target to each robot
 */
void robot_randomize_targets(void); 

/**
 * \brief	store in pointers the data for the selected robot
 * \param 	pos			pointer to store the position
 * \param 	quad		pointer to store the targeting quadrant
 * \param 	target		pointer to store the target
 * \param 	angle		pointer to store the angle
 * \param 	selected	pointer to store the selection state
 * \param 	i_id		pointer to store the inter ID
 * \param 	u_id		pointer to store the uniq ID
 */
void robot_get(	S2D * pos, S2D * quad, S2D * target, double * angle, int * selected, 
				unsigned int * i_id, unsigned int * u_id);
				
/**
 * \brief	return 1 if the selected robot is blocked
 */
int robot_get_blocked(void);

/**
 * \brief	set the selected robot as not blocked
 */
void robot_unblock(void);

/**
 * \brief	create a robot and returns its uniq ID
 * \param	x		x position of the robot
 * \param	y		y position of the robot
 * \param	angle	orientation of the robot
 */
unsigned int robot_create(double x, double y, double a);

/**
 * \brief	store a copy of the selection context
 */
void robot_push_last(void);

/**
 * \brief	pop back a stored copy the selection context
 */
void robot_pop_last(void);

/**
 * \brief	allow automatic selection of the next robot
 */
void robot_allow_increment(void);

/**
 * \brief	allow automatic selection of the next robot
 */
void robot_block_increment(void);

/**
 * \brief	manual selection of the next robot
 */
void robot_increment(void);

/**
 * \brief	move the selected robot
 * \param	dist	delta distance for the movement
 * \param	angle	delta angle for the movement
 */
void robot_move(double dist, double angle);

/**
 * \brief	set the target of every robot
 * \param	target	target for every robot
 */
void robot_set_all_targets(S2D target);

/**
 * \brief	moves the selected robot
 * \param	x		quandrant defimition (only the sign is important)
 * \param	y		quandrant defimition (only the sign is important)
 */
void robot_set_quad(double x, double y);

/**
 * \brief	select(user selection) the current robot
 */
void robot_select(void);

/**
 * \brief	deselect(user selection) the current robot
 */
void robot_deselect(void);

/**
 * \brief	deselect(user selection) every robots
 */
void robot_deselect_all(void);

/**
 * \brief	returns the number of robots
 */
int robot_get_nb(void);

unsigned short robot_get_superblocked(void);


#endif
