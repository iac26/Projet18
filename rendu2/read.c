#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "read.h"
#include "error.h"
#include "constantes.h"

//read beta LOL
//new reading pattern
/* first delete the comments.
 * the first number appearing is nb_robot
 * the following nb_robot*3 numbers are robots
 * if a fin liste is encountered before --> error
 * after reading the nb_robot*3 values there should be a FIN_LISTE
 * if there isnt -> error
 * the same for the particles!
 * */

enum{CHECKING, ERASING};
enum{NB_ROBOT, READ_ROBOT, END_ROBOT, NB_PARTICLE, END_PARTICLE, READ_PARTICLE, END};

int main (int argc, char ** argv) {
	//read_file
	if(argc > 1)
		read_file(argv[1]);	
	//process data
}

int read_file(char * filename) {
	FILE * file = fopen(filename, "r");
	char line[MAX_LINE];
	unsigned short reader_state = NB_ROBOT;
	unsigned int line_count = 0;
	int nb_robot, nb_particle, robot_count = 0, particle_count = 0;
	if (file) {
		while(fgets(line, MAX_LINE, file) != NULL) {
			line_count++;
			if((line[0]=='\n')||(line[0]=='\r')||(line[0]=='#'))
				continue;
			remove_comments(line);
			switch (reader_state) {
				case NB_ROBOT:
					if(sscanf(line, "%d", &nb_robot) == 1)
						reader_state = READ_ROBOT;
					break;
				case READ_ROBOT:
					if(detect_fin_liste(line)) {
						error_fin_liste_robots(line_count);
						return 0;
					}
					read_robot(line, &robot_count);
					if(robot_count == nb_robot)
						reader_state = END_ROBOT;
					break;
				case END_ROBOT:
					if(detect_fin_liste(line)) {
						reader_state = NB_PARTICLE;
					} else if(detect_anything(line)) {
						error_missing_fin_liste_robots(line_count);
						return 0;
					}
					break;
				case NB_PARTICLE:
					if(sscanf(line, "%d", &nb_particle) == 1)
						reader_state = READ_PARTICLE;
					break;
				case READ_PARTICLE:
					if(detect_fin_liste(line)) {
						error_fin_liste_particules(line_count);
						return 0;
					}
					read_particle(line, &particle_count);
					if(particle_count == nb_particle)
						reader_state = END_PARTICLE;
					break;
				case END_PARTICLE:
					if(detect_fin_liste(line)) {
						reader_state = END;
					} else if(detect_anything(line)) {
						error_missing_fin_liste_particules(line_count);
						return 0;
					}
					break;
				case END:
					break;
			}
		}
	} else {
		error_file_missing(filename);
		return 0;
	}
	return 1;
}

static void read_robot(char * line, int * p_robot_count) {
	double robot_x, robot_y, robot_a;
	int align = 0;
	char * start;
	char * end;
	start = line;
	double tmp;
	while(sscanf(start, "%lf", &tmp) == 1) {
		strtod(start, &end);
		start = end;
		switch (align) {
			case 0:
				robot_x = tmp;
				break;
			case 1:
				robot_y = tmp;
				break;
			case 2:
				robot_a = tmp;
				break;
		}
		align++;
		if(align == 3) {
			//printf("robot %g %g %g\n", robot_x, robot_y, robot_a);
			if(p_robot_count)
				*p_robot_count += 1;
			align = 0;
		}
		
	}
}

static void read_particle(char * line, int * p_particle_count) {
	double particle_x, particle_y, particle_r, particle_e;
	int align = 0;
	char * start;
	char * end;
	start = line;
	double tmp;
	while(sscanf(start, "%lf", &tmp) == 1) {
		strtod(start, &end);
		start = end;
		switch (align) {
			case 0:
				particle_e = tmp;
				break;
			case 1:
				particle_r = tmp;
				break;
			case 2:
				particle_x = tmp;
				break;
			case 3:
				particle_y = tmp;
				break;
		}
		align++;
		if(align == 4) {
			//printf("particle %g %g %g %g\n", particle_e, particle_r, particle_x, particle_y);
			if(p_particle_count)
				*p_particle_count += 1;
			align = 0;
		}
	}
}

static void remove_comments(char * line) {
	unsigned short comment_state = CHECKING;
	for(int i = 0; i < MAX_LINE; i++) {
		if(line[i] == '#') {
			comment_state = ERASING;
		}
		if(comment_state == ERASING) {
			line[i] = ' ';
		}
	}
}

static int detect_fin_liste(char * line) {
	char str[10];
	sscanf(line, "%10s", str);
	if(!strcmp(str, "FIN_LISTE")) {
		return 1;
	} else {
		return 0;
	}
}

static int detect_anything(char * line) {
	for(int i = 0; i < MAX_LINE; i++) {
		if((line[i] > 32)&&(line[i] <= 127)) {
			return 1;
		}
	}
	return 0;
}
