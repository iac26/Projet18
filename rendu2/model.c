#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "robot.h"
#include "particle.h"
#include "model.h"

int model_collisions() {
	robot_collision();
	particle_collision();
	cross_collision();
	return 1;
}

static void robot_collision(void) {
	int nb_robot = robot_get_nb();
	C2D a, b;
	a.rayon = R_ROBOT;
	b.rayon = R_ROBOT;
	unsigned int id_a, id_b;
	for(int i = nb_robot-1; i >= 0; i--) {
		robot_get_init(i);
		robot_get(&(a.centre.x), &(a.centre.y), NULL, NULL, &id_a);
		for(int j = i-1; j >= 0; j--) {
			robot_get(&(b.centre.x), &(b.centre.y), NULL, NULL, &id_b);
			if(util_collision_cercle(a, b, NULL)) {
				error_collision(ROBOT_ROBOT, id_a, id_b);
			}
		}
	}
}

static void particle_collision(void) {
	int nb_particle = particle_get_nb();
	C2D a, b;
	unsigned int id_a, id_b;
	for(int i = nb_particle-1; i >= 0; i--) {
		particle_get_init(i);
		particle_get(NULL, &(a.rayon), &(a.centre.x), &(a.centre.y), NULL, &id_a);
		for(int j = i-1; j >= 0; j--) {
			particle_get(NULL, &(b.rayon), &(b.centre.x), &(b.centre.y), NULL, &id_b);
			if(util_collision_cercle(a, b, NULL)) {
				//printf("r1: %lf x1: %lf y1: %lf // r2: %lf x2: %lf y2: %lf //\n", a.rayon, a.centre.x, a.centre.y, b.rayon, b.centre.x, b.centre.y);
				error_collision(PARTICULE_PARTICULE, id_a, id_b);
			}
		}
	}
}

static void cross_collision(void) {
	int nb_particle = particle_get_nb();
	int nb_robot = robot_get_nb();
	C2D a, b;
	b.rayon = R_ROBOT;
	unsigned int id_a, id_b;
	particle_get_init(nb_particle-1);
	for(int i = 0; i < nb_particle; i++) {
		particle_get(NULL, &(a.rayon), &(a.centre.x), &(a.centre.y), NULL, &id_a);
		robot_get_init(nb_robot-1);
		for(int j = 0; j < nb_robot; j++) {
			robot_get(&(b.centre.x), &(b.centre.y), NULL, NULL, &id_b);
			if(util_collision_cercle(a, b, NULL)) {
				error_collision(ROBOT_PARTICULE, id_a, id_b);
			}
		}
	}
}




