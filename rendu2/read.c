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
	unsigned short comment_state;
	unsigned short reader_state = NB_ROBOT;
	int nb_robot;
	int nb_particle;
	int robot_count = 0;
	int particle_count = 0;
	int align;
	char * token;
	double robot_x, robot_y, robot_a;
	double particle_x, particle_y, particle_r, particle_e;
	if (file) {
		while(fgets(line, MAX_LN_SIZE, file) != NULL) {
			comment_state = CHECKING;
			if((line[0]=='\n')||(line[0]=='\r')||(line[0]=='#')) {
				continue;
			}
			for(int i = 0; i < MAX_LN_SIZE; i++) {
				if(line[i] == '#') {
					comment_state = ERASING;
				}
				if(comment_state == ERASING) {
					line[i] = ' ';
				}
			}
			char fin[10];
			sscanf(line, "%10s", fin);
			if(!strcmp(fin, "FIN_LISTE")) {
				if(reader_state == ROBOT) {
					if(robot_count != nb_robot) {
						error_invalid_nb_robots();
					}
					reader_state = NB_PARTICLE;
				}
				if(reader_state == PARTICLE) {
					if(particle_count != nb_particle) {
						error_invalid_nb_particules();
					}
					reader_state = END;
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
					token = strtok(line, " ");
					align = 0;
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
							robot_count++;
						}
						token = strtok(NULL, " ");
					}
					break;
				case NB_PARTICLE:
					if(sscanf(line, "%d", &nb_particle) == 1) {
						printf("nbpart %d\n", nb_particle);
						reader_state = PARTICLE;
					}
					break;
				case PARTICLE:
					token = strtok(line, " ");
					align = 0;
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
							particle_count++;
							align = 0;
						}
						token = strtok(NULL, " ");
					}
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
