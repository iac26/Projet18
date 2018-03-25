#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "particle.h"

int main(){
	char * nom = "nom";
	FILE * write = fopen(nom,"w");
	double x, y, angle, e, rad;
	robot_create(1.0, 1.0, 0.5);
	particle_create(5, 0.2, 2.0, 3.2);
	int nb_robot, nb_particle;
	nb_robot = robot_get_nb();
	nb_particle = particle_get_nb();
	fprintf(write, "%d\n",nb_robot);
	robot_get_init_i(nb_robot);
	particle_get_init_i(nb_particle);
	for(int i = nb_robot; i > 0; i--){
		robot_get(&x, &y, &angle, NULL, NULL);
		fprintf(write, "\t%lf %lf %lf\n", x, y, angle);
	}
	fprintf(write, "FIN_LISTE\n");
	for(int i = nb_particle; i > 0; i--){
		particle_get(&e, &rad, &x, &y, NULL, NULL);
		fprintf(write, "%\tlf %lf %lf %lf\n", e, rad, x, y);
	}
	fprintf(write, "FIN_LISTE\n");
	
	return EXIT_SUCCESS;
}
