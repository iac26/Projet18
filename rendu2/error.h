#ifndef ERROR_H
#define ERROR_H

typedef enum Error_collision
{
	ROBOT_ROBOT,
	ROBOT_PARTICULE,
	PARTICULE_PARTICULE
} ERROR_COLLISION;

/**
 * \brief	correct execution
 */
void error_no_error_in_this_file();

/**
 * \brief	this needed file is missing
 * \param	file_name	missing file
 */
void error_file_missing(const char file_name[]);

/**
 * \brief	the number of robots is invalid
 */
void error_invalid_nb_robots();

/**
 * \brief	impossible to read robot data
 */
void error_invalid_robot();

/**
 * \brief	invalid robot angle. it must be within [-pi, pi]
 * \param	alpha		alpha angle
 */
void error_invalid_robot_angle(double alpha);

/**
 * \brief	an unexpected "FIN_LISTE" when reading robots
 * \param	line_number	line number of this "FIN_LISTE"
 */
void error_fin_liste_robots(unsigned int line_number);

/**
 * \brief	a "FIN_LISTE" is missing for the robots
 */
void error_missing_fin_liste_robots(unsigned int line_number);

/**
 * \brief	the number of particules is invalid
 */
void error_invalid_nb_particules();

/**
 * \brief	impossible to read particule data
 */
void error_invalid_particule();

/**
 * \brief	invalid particule data
 * \param	x0			coordonate on x-axis
 * \param	y0			coordonate on y-axis
 * \param	energy		energy of this particule
 * \param	radius		radius of this particule
 */
void error_invalid_particule_value(double energy, double radius,
								   double x0, double y0);

/**
 * \brief	Unexpected "FIN_LISTE" when reading particules
 * \param	line_number	line number of this "FIN_LISTE"
 */
void error_fin_liste_particules(unsigned int line_number);

/**
 * \brief	"FIN_LISTE" is missing for the particules
 */
void error_missing_fin_liste_particules(unsigned int line_number);

/**
 * \brief	at least one useless char has been encountered
 * \param	line_numer	line number of this useless char	
*/
void error_useless_char(unsigned int line_number);

/**
 * \brief	there is a collision
 * \param	type		type of this collision: R-R. R-P, P-P
 *                      use a symbol from the enum on lines 6-8
 * \param	id1 and id2	are the entity numbers, from 1 to nb_entity,
 * 						in the order of apparition in the test file
 * 			in case of R-P: id1 is the robot id, id2 is the particule id
 */
void error_collision(ERROR_COLLISION type, 
				     unsigned int id1, unsigned int id2);

#endif
