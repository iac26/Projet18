/**
 * \file 	graphic.h
 * \brief 	handle everything linked to glut and opengl graphics
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
 */
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
void graphic_affichage_start(void);

void graphic_affichage_end(void);

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
void graphic_robot(double x, double y, double angle, int selected);

/**
 * \brief	draws one particle on the window
 * \param	r		radius of the particle 
 * \param	x		x position of the particle
 * \param	y		y position of the particle
 */
void graphic_particle(double r, double x, double y);

/**
 * \brief	draws a point for debug purpose
 * \param	ra		radius of the point
 * \param	x		x position of the point
 * \param	y		y position of the point
 * \param	r		red color component
 * \param	g		green color component
 * \param	b		blue color component
 */
void graphic_debug(double ra, double x, double y, float r, float g, float b);

/**
 * \brief	draws the border of the simulation
 */
void graphic_border(void);

/**
 * \brief	converts the mouse coordinates into simulation coordinates
 * \param	x	pointer to the x coordinate
 * \param	y	pointer to the y coordinate
 */
void graphic_convert_mouse(double * x, double * y);

/**
 * \brief	toggles special feature
 */
void graphic_toggle_p(void);



#endif
