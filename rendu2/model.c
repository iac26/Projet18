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
		return 1;
}

static void robot_collision(void) {
	int nb_robot = robot_get_nb();
	C2D a, b;
	a.rayon = R_ROBOT;
	b.rayon = R_ROBOT;
	unsigned int id_a, id_b;
	for(int i = 0; i < nb_robot; i++) {
		robot_get_init(i);
		robot_get(&(a.centre.x), &(a.centre.y), NULL, NULL, &id_a);
		for(int j = i+1; j < nb_robot; j++) {
			robot_get(&(b.centre.x), &(b.centre.y), NULL, NULL, &id_b);
			if(util_collision_cercle(a, b, NULL)) {
				error_collision(ROBOT_ROBOT, id_a, id_b);
			}
		}
	}
}

static void particle_collision(void) {
	
}

static void cross_collision(void) {

}




