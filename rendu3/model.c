#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "robot.h"
#include "particle.h"
#include "model.h"


int initial_collisions(){
	unsigned int id_a, id_b;
	if(robot_collision(NULL, &id_a, &id_b)){
		error_collision(ROBOT_ROBOT, id_a, id_b);
		return 0;
	}
	if(particle_collision(NULL, &id_a, &id_b)){
		error_collision(PARTICULE_PARTICULE, id_a, id_b);
		return 0;
	}
	if(cross_collision(NULL, &id_a, &id_b)){
		error_collision(ROBOT_PARTICULE, id_b, id_a);
		return 0;
	}
	return 1;
}

static int robot_collision(	double * p_dist, unsigned int * p_id_a, 
							unsigned int * p_id_b){
	int nb_robot = robot_get_nb();
	C2D a, b;
	a.rayon = R_ROBOT;
	b.rayon = R_ROBOT;
	unsigned int id_a, id_b;
	for(int i = nb_robot-1; i >= 0; i--){
		robot_get_init_i(i);
		robot_get(&a.centre, NULL, NULL, NULL, &id_a);
		for(int j = i-1; j >= 0; j--){
			robot_get(&b.centre, NULL, NULL, NULL, &id_b);
			if(util_collision_cercle(a, b, p_dist)){
				if(p_id_a)
					*p_id_a = id_a;
				if(p_id_b)
					*p_id_b = id_b;
				return 1;
			}
		}
	}
	return 0;
}

static int particle_collision(	double * p_dist, unsigned int * p_id_a, 
								unsigned int * p_id_b){
	int nb_particle = particle_get_nb();
	C2D a, b;
	unsigned int id_a, id_b;
	for(int i = nb_particle-1; i >= 0; i--){
		particle_get_init_i(i);
		particle_get(NULL, &(a.rayon), &(a.centre.x), &(a.centre.y), NULL, &id_a);
		for(int j = i-1; j >= 0; j--){
			particle_get(NULL, &(b.rayon), &(b.centre.x), &(b.centre.y), NULL, &id_b);
			if(util_collision_cercle(a, b, p_dist)){
				if(p_id_a)
					*p_id_a = id_a;
				if(p_id_b)
					*p_id_b = id_b;
				return 1;
			}
		}
	}
	return 0;
}

static int cross_collision(	double * p_dist, unsigned int * p_id_a, 
							unsigned int * p_id_b){
	int nb_particle = particle_get_nb();
	int nb_robot = robot_get_nb();
	C2D a, b;
	b.rayon = R_ROBOT;
	unsigned int id_a, id_b;
	particle_get_init_i(nb_particle-1);
	for(int i = 0; i < nb_particle; i++){
		particle_get(NULL, &(a.rayon), &(a.centre.x), &(a.centre.y), NULL, &id_a);
		robot_get_init_i(nb_robot-1);
		for(int j = 0; j < nb_robot; j++){
			robot_get(&b.centre, NULL, NULL, NULL, &id_b);
			if(util_collision_cercle(a, b, p_dist)){
				if(p_id_a)
					*p_id_a = id_a;
				if(p_id_b)
					*p_id_b = id_b;
				return 1;
			}
		}
	}
	return 0;
}

static void target_all(double x, double y){
	robot_get_init_head();
	for(int n = robot_get_nb(); n != 0; n -= 1 ){
		S2D a;
		a.x = x;
		a.y = y;
		robot_set_target(a);
	}
}

void update(void) {
	target_all(5, 6);
	robot_block_increment();
	robot_get_init_head();
	for(int n = robot_get_nb(); n != 0; n -= 1){
		double alpha = calculate_angle();
		robot_move(alpha);
		printf("move done %d\n", n);
		robot_print();
		particle_print();
	}
}





