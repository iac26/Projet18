#ifndef GRAPHIC_H
#define GRAPHIC_H

#define WIDTH 800
#define HEIGHT 800

/**
 * \brief	initialize the glut stuff
 * \param	argc	argument count for glut
 * \param	argv	arguments for glut
 */
int graphic_init_glut(int * argc, char ** argv);

/**
 * \brief	glut draw callback function
 */
void graphic_affichage(void);

/**
 * \brief	glut reshape callback function
 * \param	w		window width
 * \param	h		window height
 */
void graphic_reshape(int w, int h);

/**
 * \brief	draws one robot on the window
 * \param	x		x position of the robot
 * \param	y		y position of the robot
 * \param	angle	orientation of the robot
 */
void graphic_robot(double x, double y, double angle);

/**
 * \brief	draws one particle on the window
 * \param	r		radius of the particle 
 * \param	x		x position of the particle
 * \param	y		y position of the particle
 */
void graphic_particle(double r, double x, double y);

/**
 * \brief	draws the border of the simulation
 */
void graphic_border(void);



#endif
