#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "read.h"
#include "error.h"
#include "robot.h"
#include "particle.h"
#include "constantes.h"
#include "utilitaire.h"


enum{CHECKING, ERASING};
enum{NB_ROBOT, READ_ROBOT, END_ROBOT, NB_PARTICLE, END_PARTICLE, READ_PARTICLE, END};
static int robot_count;
static int particle_count;
static unsigned int line_count = 0;
static char line[MAX_LINE];
static unsigned short reader_state = NB_ROBOT;
static int nb_robot, nb_particle;

int read_file(char * filename) {
	FILE * file = fopen(filename, "r");
	robot_count = 0;
	particle_count = 0;
	if (file) {
		while(fgets(line, MAX_LINE, file) != NULL) {
			line_count++;
			remove_comments(line);
			if(!detect_anything(line))
				continue;
			switch (reader_state) {
				case NB_ROBOT:
					if(!read_nb_robot_step())
						return 0;
					break;
				case READ_ROBOT:
					if(!read_robot_step())
						return 0;
					break;
				case END_ROBOT:
					if(!read_end_robot_step())
						return 0;
					break;
				case NB_PARTICLE:
					if(!read_nb_particle_step())
						return 0;
					break;
				case READ_PARTICLE:
					if(!read_particle_step())
						return 0;
					break;
				case END_PARTICLE:
					if(!read_end_particle_step())
						return 0;
					break;
				case END:
					break;
			}
			reset_str(line);
		}
	} else {
		error_file_missing(filename);
		return 0;
	}
	error_no_error_in_this_file();
	return 1;
}

static int read_nb_robot_step(void){
	if(sscanf(line, "%d", &nb_robot) == 1) {
		reader_state = READ_ROBOT;
	} else {
		error_invalid_nb_robots();
		return 0;
	}
	if(nb_robot < 0) {
		error_invalid_nb_robots();
		return 0;
	}
	return 1;
}

static int read_robot_step(void){
	if(detect_fin_liste(line)) {
		error_fin_liste_robots(line_count);
		return 0;
	}
	if(!read_robot(line))
		return 0;
	if(robot_count == nb_robot)
		reader_state = END_ROBOT;
	return 1;
}

static int read_end_robot_step(void){
	if(detect_fin_liste(line)) {
		reader_state = NB_PARTICLE;
	} else if(detect_anything(line)){
		error_missing_fin_liste_robots(line_count);
		return 0;
	}
	return 1;
}
 
static int read_nb_particle_step(void){
	if(sscanf(line, "%d", &nb_particle) == 1) {
		reader_state = READ_PARTICLE;
	} else {
		error_invalid_nb_particules();
		return 0;
	}
	if(nb_robot < 0) {
		error_invalid_nb_particules();
		return 0;
	}
	return 1;
}
 
static int read_particle_step(void){
	if(detect_fin_liste(line)) {
		error_fin_liste_particules(line_count);
		return 0;
	}
	if(!read_particle(line)) 
		return 0;
	if(particle_count == nb_particle)
		reader_state = END_PARTICLE;
	return 1;
}

static int read_end_particle_step(void){
	if(detect_fin_liste(line)) {
		reader_state = END;
	} else if(detect_anything(line)) {
		error_missing_fin_liste_particules(line_count);
		return 0;
	}
	return 1;
}
 

void read_save(char * filename) {
	FILE * file = fopen(filename,"w");
	double x, y, angle, e, rad;
	int nb_robot, nb_particle;
	nb_robot = robot_get_nb();
	nb_particle = particle_get_nb();
	robot_get_init_i(nb_robot-1);
	particle_get_init_i(nb_particle-1);
	fprintf(file, "# \"%s\" computer generated save file\n\n", filename);
	fprintf(file, "%d\n", nb_robot);
	for(int i = 0; i < nb_robot; i++){
		robot_get(&x, &y, &angle, NULL, NULL);
		fprintf(file, "\t %2.5lf %2.5lf %2.5lf\n", x, y, angle);
	}
	fprintf(file, "FIN_LISTE\n\n");
	
	fprintf(file, "%d\n", nb_particle);
	for(int i = 0; i < nb_particle; i++){
		particle_get(&e, &rad, &x, &y, NULL, NULL);
		fprintf(file, "%\t %2.5lf %2.5lf %2.5lf %2.5lf\n", e, rad, x, y);
	}
	fprintf(file, "FIN_LISTE\n\n");
	fclose(file);
}

static int read_robot(char * line) {
	S2D a;
	double robot_a;
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
				a.x = tmp;
				break;
			case 1:
				a.y = tmp;
				break;
			case 2:
				robot_a = tmp;
				break;
		}
		align++;
		if(align == 3) {
			if(util_point_dehors(a, DMAX)||util_alpha_dehors(robot_a)) {
				error_invalid_robot_angle(robot_a);
				return 0;
			}
			robot_create(a.x, a.y, robot_a);
			//printf("robot %g %g %g\n", robot_x, robot_y, robot_a);
			robot_count++;
			align = 0;
		}
		
	}
	return 1;
}

static int read_particle(char * line) {
	C2D a;
	double particle_e;
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
				a.rayon = tmp;
				break;
			case 2:
				a.centre.x = tmp;
				break;
			case 3:
				a.centre.y = tmp;
				break;
		}
		align++;
		if(align == 4) {
			if(	util_point_dehors(a.centre, DMAX)||(particle_e > E_PARTICULE_MAX)||
				(a.rayon > R_PARTICULE_MAX)||(a.rayon < R_PARTICULE_MIN)) {
				error_invalid_particule_value(particle_e, a.rayon, a.centre.x, a.centre.y);
				return 0;
			}
			particle_create(particle_e, a.rayon, a.centre.x, a.centre.y);
			particle_count++;
			align = 0;
		}
	}
	return 1;
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

static void reset_str(char * line) {
	for (int i = 0; i < MAX_LINE; i++) {
		line[i] = ' ';
	}
}
