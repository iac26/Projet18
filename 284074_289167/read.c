/**
 * \file 	read.c
 * \brief 	file reader and writer
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
 */
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


#define FIN_LISTE_LEN 10
#define ASCII_SPACE 32
#define ASCII_LAST 127

typedef enum eraser{CHECKING, ERASING} ERASER;
typedef enum reader{NB_ROBOT, READ_ROBOT, END_ROBOT, NB_PARTICLE,
					END_PARTICLE, READ_PARTICLE, END} READER;
typedef enum robot_field{R_X, R_Y, R_ANGLE, R_END} ROBOT_FIELD;
typedef enum particle_field{P_ENERGY, P_RADIUS, P_X, P_Y, P_END} PARTICLE_FIELD;


static int robot_count;
static int particle_count;
static unsigned int line_count = 0;
static READER reader_state;
static char line[MAX_LINE];
static int nb_robot, nb_particle;

int read_file(char * filename){
	FILE * file = fopen(filename, "r");
	reader_state = NB_ROBOT;
	line_count = 0;
	robot_count = 0;
	particle_count = 0;
	if(file){
		while(fgets(line, MAX_LINE, file) != NULL){
			line_count++;
			remove_comments(line);
			if(!detect_anything(line))
				continue;
			switch(reader_state){
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
	#ifdef DEBUG
	robot_print();
	particle_print();
	#endif
	return 1;
}

static int read_nb_robot_step(void){
	if(sscanf(line, "%d", &nb_robot) == 1){
		reader_state = READ_ROBOT;
	} else {
		error_invalid_nb_robots();
		return 0;
	}
	if(nb_robot < 0){
		error_invalid_nb_robots();
		return 0;
	}
	return 1;
}

static int read_robot_step(void){
	if(detect_fin_liste(line)){
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
	if(detect_fin_liste(line)){
		reader_state = NB_PARTICLE;
	} else {
		error_missing_fin_liste_robots(line_count);
		return 0;
	}
	return 1;
}
 
static int read_nb_particle_step(void){
	if(sscanf(line, "%d", &nb_particle) == 1){
		reader_state = READ_PARTICLE;
	} else {
		error_invalid_nb_particules();
		return 0;
	}
	if(nb_robot < 0){
		error_invalid_nb_particules();
		return 0;
	}
	return 1;
}
 
static int read_particle_step(void){
	if(detect_fin_liste(line)){
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
	if(detect_fin_liste(line)){
		reader_state = END;
	} else {
		error_missing_fin_liste_particules(line_count);
		return 0;
	}
	return 1;
}
 

void read_save(char * filename){
	FILE * file = fopen(filename,"w");
	if(file) {
		double angle, e;
		int nb_robot, nb_particle;
		nb_robot = robot_get_nb();
		nb_particle = particle_get_nb();
		robot_get_init_i(nb_robot-1);
		particle_get_init_i(nb_particle-1);
		fprintf(file, "# \"%s\" computer generated save file\n\n", filename);
		fprintf(file, "%d\n", nb_robot);
		S2D rob;
		C2D part;
		for(int i = 0; i < nb_robot; i++){
			robot_get(&rob, NULL, NULL, &angle, NULL, NULL, NULL);
			fprintf(file, "\t %2.5lf %2.5lf %2.5lf\n", rob.x, rob.y, angle);
		}
		fprintf(file, "FIN_LISTE\n\n");
		
		fprintf(file, "%d\n", nb_particle);
		for(int i = 0; i < nb_particle; i++){
			particle_get(&e, &part, NULL, NULL);
			fprintf(file, "\t %2.5lf %2.5lf %2.5lf %2.5lf\n", e, part.rayon, 
					part.centre.x, part.centre.y);
		}
		fprintf(file, "FIN_LISTE\n\n");
		fclose(file);
	}
}

static int read_robot(char * line){
	S2D a;
	double robot_a;
	ROBOT_FIELD align = 0;
	char * start;
	char * end;
	start = line;
	double tmp;
	int check = 0;
	while(check != EOF){
		check = sscanf(start, "%lf", &tmp);
		if(check == 0) {
			error_invalid_robot();
			return 0;
		}
		strtod(start, &end);
		start = end;
		switch (align){
			case R_X:
				a.x = tmp;
				break;
			case R_Y:
				a.y = tmp;
				break;
			case R_ANGLE:
				robot_a = tmp;
				break;
			default:
				break;
		}
		align++;
		if(align == R_END){
			if(util_alpha_dehors(robot_a)){
				error_invalid_robot_angle(robot_a);
				return 0;
			}
			if(util_point_dehors(a, DMAX)) {
				error_invalid_robot();
				return 0;
			}
			robot_create(a.x, a.y, robot_a);
			robot_count++;
			align = 0;
		}
		
	}
	return 1;
}

static int read_particle(char * line){
	C2D a;
	double particle_e;
	PARTICLE_FIELD align = 0;
	char * start;
	char * end;
	start = line;
	double tmp;
	int check = 0;
	while(check != EOF){
		check = sscanf(start, "%lf", &tmp);
		if(check == 0) {
			error_invalid_particule();
			return 0;
		}
		strtod(start, &end);
		start = end;
		switch (align){
			case P_ENERGY:
				particle_e = tmp;
				break;
			case P_RADIUS:
				a.rayon = tmp;
				break;
			case P_X:
				a.centre.x = tmp;
				break;
			case P_Y:
				a.centre.y = tmp;
				break;
			default:
				break;
		}
		align++;
		if(align == P_END){
			if(	util_point_dehors(a.centre, DMAX)||(particle_e > E_PARTICULE_MAX)||
				(a.rayon > R_PARTICULE_MAX)||(a.rayon < R_PARTICULE_MIN)){
				error_invalid_particule_value(	particle_e, a.rayon, a.centre.x, 
												a.centre.y);
				return 0;
			}
			particle_create(particle_e, a.rayon, a.centre.x, a.centre.y);
			particle_count++;
			align = 0;
		}
	}
	return 1;
}

static void remove_comments(char * line){
	ERASER comment_state = CHECKING;
	for(int i = 0; i < MAX_LINE; i++){
		if(line[i] == '#'){
			comment_state = ERASING;
		}
		if(comment_state == ERASING){
			line[i] = ' ';
		}
	}
}

static int detect_fin_liste(char * line){
	char str[FIN_LISTE_LEN];
	sscanf(line, "%9s", str);
	if(!strcmp(str, "FIN_LISTE")){
		return 1;
	} else {
		return 0;
	}
}

static int detect_anything(char * line){
	for(int i = 0; i < MAX_LINE; i++){
		if((line[i] > ASCII_SPACE)&&(line[i] <= ASCII_LAST)){
			return 1;
		}
	}
	return 0;
}

static void reset_str(char * line){
	for (int i = 0; i < MAX_LINE; i++){
		line[i] = ' ';
	}
}

void read_file_ok(void) {
	error_no_error_in_this_file();
} 
