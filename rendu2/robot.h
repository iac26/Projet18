#ifndef ROBOT_H
#define ROBOT_H

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
 * \brief	returns one robot, the first one selected by robot_get_init*
 * 			the next ones sequentially
 * \param	x		pointer to store the x position of the robot
 * \param	y		pointer to store the y position of the robot
 * \param	angle	pointer to store the orientation of the robot
 * \param	i_id	pointer to store the iter ID of the robot
 * \param	u_id	pointer to store the uniq ID of the robot
 */
void robot_get(double * x, double * y, double * angle, unsigned int * i_id, unsigned int * u_id);

/**
 * \brief	create a robot and returns its uniq ID
 * \param	x		x position of the robot
 * \param	y		y position of the robot
 * \param	angle	orientation of the robot
 */
unsigned int robot_create(double x, double y, double a);

/**
 * \brief	returns the number of robots
 */
int robot_get_nb(void);


#endif
