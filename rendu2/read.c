#include <stdio.h>
#include <math.h>
#include <string.h>

#include "read.h"
#include "error.h"
#include "constantes.h"

//read beta LOL

#define MAX_LN_SIZE 100
enum{CHECKING, ERASING};
enum{NB_ROBOT, ROBOT, NB_PARTICLE, PARTICLE, END};

int main (int argc, char ** argv) {
	//read_file
	if(argc > 1)
	read_file(argv[1]);
	
	//process data
}

static int read_file(char * filename) {
	FILE * file = fopen(filename, "r");
	char line[MAX_LN_SIZE];
	unsigned short reader_state = NB_ROBOT;
	int nb_robot;
	int nb_particle;
	int robot_count = 0;
	int particle_count = 0;
	if (file) {
		while(fgets(line, MAX_LN_SIZE, file) != NULL) {
			if((line[0]=='\n')||(line[0]=='\r')||(line[0]=='#')) {
				continue;
			}
			if(detect_fin_liste(line)) {
				switch (reader_state) {
					case ROBOT:
						if(robot_count != nb_robot) {
							error_invalid_nb_robots();
						}
						reader_state = NB_PARTICLE;
						break;
					case PARTICLE: 
						if(particle_count != nb_particle) {
							error_invalid_nb_particules();
						}
						reader_state = END;
						break;
				}
				continue;
			}
			switch (reader_state) {
				case NB_ROBOT:
					if(sscanf(line, "%d", &nb_robot) == 1) {
						printf("nbrobot %d\n", nb_robot);
						reader_state = ROBOT;
					}
					break;
				case ROBOT:
					read_robot(line, &robot_count);
					break;
				case NB_PARTICLE:
					if(sscanf(line, "%d", &nb_particle) == 1) {
						printf("nbpart %d\n", nb_particle);
						reader_state = PARTICLE;
					}
					break;
				case PARTICLE:
					read_particle(line, &particle_count);
					break;
				case END:
					break;
			}
		}
		printf("ended\n");
	} else {
		error_file_missing(filename);
	}
	return 1;
}

static void read_robot(char * line, int * p_robot_count) {
	double robot_x, robot_y, robot_a;
	int align = 0;
	char * token = strtok(line, " ");
	while(token) {
		double tmp;
		if(sscanf(token, "%lf", &tmp) == 1) {
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
		}
		if(align == 3) {
			printf("robot %g %g %g\n", robot_x, robot_y, robot_a);
			if(p_robot_count)
				*p_robot_count += 1;
		}
		token = strtok(NULL, " ");
	}
}

static void read_particle(char * line, int * p_particle_count) {
	double particle_x, particle_y, particle_r, particle_e;
	int align = 0;
	char * token = strtok(line, " ");
	while(token) {
		double tmp;
		if(sscanf(token, "%lf", &tmp) == 1) {
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
		}
		if(align == 4) {
			printf("particle %g %g %g %g\n", particle_e, particle_r, particle_x, particle_y);
			if(p_particle_count)
				*p_particle_count += 1;
			align = 0;
		}
		token = strtok(NULL, " ");
	}
}

static void remove_comments(char * line) {
	unsigned short comment_state = CHECKING;
	for(int i = 0; i < MAX_LN_SIZE; i++) {
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
