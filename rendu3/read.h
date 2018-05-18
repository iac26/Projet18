/**
 * \file 	read.h
 * \brief 	file reader and writer
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#ifndef READ_H
#define READ_H

/**
 * \brief	read a file and store the data contained in the file
 * \param	filename	the name of the file to read
 */
int read_file(char * filename);

/**
 * \brief	save a file which will contain the simulation data
 * \param	filename	the name of the file to save
 */
void read_save(char * filename);

/**
 * \brief	reads and stores all the robots on a line
 * \param	line		the line from which the robots will be read
 */
static int read_robot(char * line);

/**
 * \brief	reads and stores all the particles on a line
 * \param	line		the line from which the particles will be read
 */
static int read_particle(char * line);

/**
 * \brief	removes any char preceded by '#' on a string
 * \param	line		the string from which comments are to be removed
 */
static void remove_comments(char * line);

/**
 * \brief	detects if the "FIN_LISTE" token is ona string
 * \param	line		the input string to detect from
 */
static int detect_fin_liste(char * line);

/**
 * \brief	detects if the line contains "visible" chars
 * \param	line		the input string
 */
static int detect_anything(char * line);

/**
 * \brief	fill a string with ' '
 * \param	line		string to reset
 */
static void reset_str(char * line);

/**
 * \brief	reader step which reads the number of robots
 */
static int read_nb_robot_step(void); 

/**
 * \brief	reader step that reads the robots
 */
static int read_robot_step(void);

/**
 * \brief	reader step that looks for "FIN_LISTE"
 */ 
static int read_end_robot_step(void); 

/**
 * \brief	reader step which reads the number of particles
 */
static int read_nb_particle_step(void); 

/**
 * \brief	reader step that reads the particles
 */
static int read_particle_step(void); 

/**
 * \brief	reader step that looks for "FIN_LISTE"
 */ 
static int read_end_particle_step(void); 

/**
 * \brief	calls the error module to signal that no error was found in a file
 */
void read_file_ok(void);


#endif
