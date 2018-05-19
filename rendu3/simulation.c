/**
 * \file 	simulation.c
 * \brief 	handles the simulation
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "robot.h"
#include "particle.h"
#include "simulation.h"
#include "graphic.h"

#define ROT_STEP DELTA_VROT
#define TRAN_STEP DELTA_VTRAN
#define OPTIMAL_ANGLE M_PI/3.0
#define BLOCK_TRIGGER 10
#define BLOCK_EXTREME_TRIGGER 100
#define DEBUG_RAYON 0.2f
static int manual_control;

static double manual_v_rot;
static double manual_v_tran;

static int first;



int simulation_initial_collisions(){
	unsigned int id_a, id_b;
	particle_allow_increment();
	robot_allow_increment();
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
		robot_get(&(a.centre), NULL, NULL, NULL, NULL, NULL, &id_a);
		for(int j = i-1; j >= 0; j--){
			robot_get(&(b.centre), NULL, NULL, NULL, NULL, NULL, &id_b);
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
		particle_get(NULL, &a, NULL, &id_a);
		for(int j = i-1; j >= 0; j--){
			particle_get(NULL, &b, NULL, &id_b);
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
		particle_get(NULL, &a, NULL, &id_a);
		robot_get_init_i(nb_robot-1);
		for(int j = 0; j < nb_robot; j++){
			robot_get(&(b.centre), NULL, NULL, NULL, NULL, NULL, &id_b);
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

static int single_collisions_robot(	C2D _this, C2D new_this, double * tran,
										int * collisions, unsigned u_id) {
	C2D other;
	other.rayon = R_ROBOT;
	double dist;
	unsigned int other_id;
	robot_get(&(other.centre), NULL, NULL, NULL, NULL, NULL, &other_id);
	if(u_id != other_id) {
		if(util_collision_cercle(new_this, other, &dist)) {
			*collisions = 1;
			double L = util_distance(_this.centre, other.centre);
			double n_tran;
			if(util_inner_triangle(*tran, dist, L, R_ROBOT+R_ROBOT, &n_tran)) {
				*tran = n_tran;
			} else {
				*tran = 0;
			}	
		}
		return 0;
	}	
	return 1;							
}

static int single_collisions_particle(	C2D _this, C2D new_this, double angle, 
										double * tran, int * collisions, int * eaten) {
	double dist;
	C2D part;
	unsigned int part_uid;
	particle_get(NULL, &part, NULL, &part_uid);
	if(util_collision_cercle(new_this, part, &dist)) {
		*collisions = 1;
		double L = util_distance(_this.centre, part.centre);
		double n_tran;
		if(util_inner_triangle(*tran, dist, L, R_ROBOT+part.rayon, &n_tran)) {
			*tran = n_tran;
		} else {
			*tran = 0;
		}
		new_this.centre = util_deplacement(_this.centre, angle, *tran);
		if(util_alignement(new_this.centre, angle, part.centre)) {
			*eaten = part_uid;
		}
		return 0;	
	}
	return 1;																				
}

static int single_collisions(	C2D _this, double angle, double tran, double rot, 
								unsigned int u_id) {
	robot_push_last(); 
	int collisions = 1, step = 0, eaten = 0;
	int nb_robot = robot_get_nb();
	int nb_particle = particle_get_nb();
	C2D new_this; 
	new_this.rayon = R_ROBOT; 
	robot_block_increment();
	particle_block_increment();
	while(collisions) {
		step++;
		collisions = 0;
		new_this.centre = util_deplacement(_this.centre, angle, tran);
		robot_get_init_head();
		for(int i = 0; i < nb_robot; i++) {
			single_collisions_robot(_this, new_this, &tran, &collisions, u_id);
			new_this.centre = util_deplacement(_this.centre, angle, tran);
			robot_increment();
		}
		particle_get_init_head();
		for(int i = 0; i < nb_particle; i++) {
			single_collisions_particle(	_this, new_this, angle, &tran, &collisions,
										&eaten);
			new_this.centre = util_deplacement(_this.centre, angle, tran);
			particle_increment();
		}
	}	
	robot_pop_last();
	robot_move(tran, rot);
	if(eaten) {
		particle_delete_u(eaten);
	}

	return eaten;
}

static void move(void) {
	C2D c_robot;
	S2D targ;
	unsigned int id;
	double c_angle;
	double v_tran = 0, v_rot = 0;
	double delta_angle;
	int selected;
	c_robot.rayon = R_ROBOT;
	robot_get(&(c_robot.centre), NULL, &targ, &c_angle, &selected, NULL, &id);
	if(!selected) {
		if(util_ecart_angle(c_robot.centre, c_angle, targ, &delta_angle)) {
			if(fabs(delta_angle) < OPTIMAL_ANGLE) {
				if(VTRAN_MAX*DELTA_T > util_distance(c_robot.centre, targ)) {
					v_tran = util_distance(c_robot.centre, targ);
				} else {
					v_tran = VTRAN_MAX;
				}
			}
			if(fabs(delta_angle) < VROT_MAX*DELTA_T) {
				v_rot = delta_angle;
			} else {
				if(delta_angle < 0) {
					v_rot = -VROT_MAX;
				} else {
					v_rot = VROT_MAX;
				}
			}
		}
	} else {
		v_rot = manual_v_rot;
		v_tran = manual_v_tran;
	}
	if(single_collisions(	c_robot, c_angle, v_tran*DELTA_T,
							v_rot*DELTA_T, id)) {
		robot_unblock();
	}
}

void simulation_update(void) {
	robot_block_increment();
	int nb_robot = robot_get_nb();
	if(first) {
		first = 0;
		simulation_assign_quads();
	}
	if(particle_get_event()) {
		simulation_select_targets();
	}
	simulation_handle_blocked();
	robot_get_init_head();
	for(int i = 0; i < nb_robot; i++) {
		move();
		robot_increment();
	}
	particle_decomposition();
}

static void select_in_quads(void) {
	int nb_robot = robot_get_nb(), nb_part = particle_get_nb(), part_count = 0;
	robot_block_increment();
	particle_block_increment();
	particle_untarget_all();
	robot_get_init_head();
	for(int i = 0; i < nb_robot; i++) {
		if(!robot_get_blocked()) {
			robot_unset_target();
		}
		robot_increment();
	}
	C2D part;
	S2D rob, quad;
 	particle_get_init_head();
 	for(int i = 0; i < nb_part; i++) {
 		particle_get(NULL, &part, NULL, NULL);
 		unsigned closest_id_quad, id, found_quad = 0;
		double closest_d_quad = 2*DMAX;
		robot_get_init_head();
		for(int i = 0; i < nb_robot; i++) {
			if(!robot_get_blocked() && !robot_has_target()) {
				robot_get(&rob, &quad, NULL, NULL, NULL, NULL, &id);
				double d = util_distance(rob, part.centre);
				if(d < closest_d_quad) {
					if(quad.x * part.centre.x >= 0 && quad.y * part.centre.y >= 0) {
						closest_id_quad = id;
						closest_d_quad = d;
						found_quad = 1;
					} 
				}
			}
			robot_increment();
		}
		if(found_quad) {
			particle_target();
			robot_get_init_u(closest_id_quad);
			robot_set_target(part.centre);
		}
		particle_increment();
 	}
 	robot_get_init_head();
 	particle_get_init_head();
 	for(int i = 0; i < nb_robot; i++) {
 		if(!robot_get_blocked() && !robot_has_target()) {
 			while(particle_targeted()) {
 				if(part_count >= nb_part)
 					return;
 				particle_increment();
 				part_count++;
 			}
 			particle_get(NULL, &part, NULL, NULL);
 			robot_set_target(part.centre);
 			particle_target();
 		}
 	}
}

static void select_decomp_finished(void) {
	int nb_robot = robot_get_nb();
	int nb_part = particle_get_nb();
	robot_block_increment();
	particle_block_increment();
	robot_get_init_head();
	C2D part;
	S2D rob;
	S2D quad;
	for(int i = 0; i < nb_robot; i++) {
		if(!robot_get_blocked()) {
			robot_get(&rob, &quad, NULL, NULL, NULL, NULL, NULL);
			S2D closest;
			S2D closest_quad;
			double closest_d = 2*DMAX;
			double closest_d_quad = 2*DMAX;
			unsigned int found = 0;
			particle_get_init_head();
			for(int i = 0; i < nb_part; i++) {
				particle_get(NULL, &part, NULL, NULL);
				double d = util_distance(rob, part.centre);
				if(d < closest_d_quad) {
					if(quad.x * part.centre.x >= 0 && quad.y * part.centre.y >= 0) {
						closest_quad = part.centre;
						closest_d_quad = d;
						found = 1;
					} 
				}
				if(d < closest_d) {
					closest_d = d;
					closest = part.centre;
				}
				particle_increment();
			}
			if(found) {
				robot_set_target(closest_quad);
			} else {
				robot_set_target(closest);
			}
		}
		robot_increment();
	}
}

void simulation_select_targets(void) {
	particle_untarget_all();
	if(particle_decomp_finished()) {
		select_decomp_finished();
	} else {
		select_in_quads();
	}
}

void simulation_handle_blocked(void) {
	robot_block_increment();
	particle_block_increment();
	robot_get_init_head();
	int nb_robots = robot_get_nb();
	int nb_part = particle_get_nb();
	for(int i = 0; i < nb_robots; i++) {
		if(robot_get_blocked()) {
			unsigned id;
			S2D rob;
			C2D part;
			robot_get(&rob, NULL, NULL, NULL, NULL, &id, NULL);
			particle_get_init_head();
			S2D second_closest;
			S2D closest;
			double closest_d = 2*DMAX; // a "very big" distance
			for(int i = 0; i < nb_part; i++) {
				particle_get(NULL, &part, NULL, NULL);
				double d = util_distance(rob, part.centre);
				if((d < closest_d)) {
					second_closest = closest;
					closest_d = d;
					closest = part.centre;
				}
				particle_increment();
			}
			if(robot_get_blocked() > BLOCK_EXTREME_TRIGGER){
				robot_randomize_targets();
				return;
			}
			if(robot_get_blocked() > BLOCK_TRIGGER) {
				robot_set_target(second_closest);
			} else {
				robot_set_target(closest);
			}
		}
		robot_increment();
	}
}

void simulation_set_manual_control(void) {
	manual_control = 1;
}

void simulation_set_auto_control(void){
	manual_control = 0;
	robot_deselect_all();
}

int simulation_get_control_mode(void){
	return manual_control;
}

void simulation_select(S2D point) {
	if(manual_control) {
		robot_deselect_all();
		C2D rob;
		int selected;
		rob.rayon = R_ROBOT;
		int nb_robot = robot_get_nb();
		robot_push_last();
		robot_get_init_head();
		robot_block_increment();
		for(int i = 0; i < nb_robot; i++) {
			robot_get(&(rob.centre), NULL, NULL, NULL, &selected, NULL, NULL);
			if(util_point_dans_cercle(point, rob)) {
				if(selected) {
					robot_deselect();
				} else {
					robot_select();
				}
				break;
			}
			robot_increment();
		}
		robot_allow_increment();
		robot_pop_last();
	}
}

void simulation_man_for(void){
	if(manual_control) {
		if(manual_v_tran <= VTRAN_MAX)
			manual_v_tran += TRAN_STEP;
	}
}

void simulation_man_back(void){
	if(manual_control) {
		if(manual_v_tran >= -VTRAN_MAX)
			manual_v_tran -= TRAN_STEP;
	}
}

void simulation_man_left(void){
	if(manual_control) {
		if(manual_v_rot <= VROT_MAX)
			manual_v_rot += ROT_STEP;
	}
}

void simulation_man_right(void){
	if(manual_control) {
		if(manual_v_rot >= -VROT_MAX)
			manual_v_rot -= ROT_STEP;
	}
}

void simulation_reset_man(void) {
	manual_v_rot = 0;
	manual_v_tran = 0;
}

double simulation_get_man_vrot(void) {
	return manual_v_rot;
}

double simulation_get_man_vtran(void) {
	return manual_v_tran;
}

void simulation_init(void) {
	first = 1;
	robot_delete_all();
	particle_delete_all();
}

void simulation_assign_quads(void) {
	robot_block_increment();
	robot_get_init_head();
	int nb_robot = robot_get_nb(), rob_per_quad = nb_robot / 4, fill = 0;
	S2D rob;
	int pospos=0, negpos=0, negneg=0, posneg=0;
	for(int i = 0; i < nb_robot; i++) {
		robot_get(&rob, NULL, NULL, NULL, NULL, NULL, NULL);
		if(rob_per_quad == 0) {
			robot_set_quad(0, 0);
		}
		else if(rob.x >= 0 && rob.y >= 0) {
			robot_set_quad(1, 1);
			if(pospos >= rob_per_quad) {
				fill = 1;
			}
			pospos++;
		}
		else if(rob.x < 0 && rob.y >= 0) {
			robot_set_quad(-1, 1);
			if(negpos >= rob_per_quad) {
				fill = 1;
			}
			negpos++;
		}
		else if(rob.x < 0 && rob.y < 0) {
			robot_set_quad(-1, -1);
			if(negneg >= rob_per_quad) {
				fill = 1;
			}
			negneg++;
		}
		else if(rob.x >= 0 && rob.y < 0) {
			robot_set_quad(1, -1);
			if(posneg >= rob_per_quad) {
				fill = 1;
			}
			posneg++;
		}
		if(fill) {
			if(pospos < rob_per_quad) {
				robot_set_quad(1, 1);
				pospos++;
			} else if(negpos < rob_per_quad) {
				robot_set_quad(-1, 1);
				negpos++;
			} else if(negneg < rob_per_quad) {
				robot_set_quad(-1, -1);
				negneg++;
			} else if(posneg < rob_per_quad) {
				robot_set_quad(1, -1);
				posneg++;
			}
		}
		robot_increment();
	}
}

double simulation_get_rate(void) {
	double tot_energy = particle_get_tot_energy();
	if(tot_energy) {
		return (particle_get_elim_energy() / tot_energy) * 100;
	}
	return 0;
}

int simulation_get_finished(void) {
	return particle_finished();
}

void simulation_print_everything(void) {
	graphic_affichage_start();
	double a;
	int sel;
	S2D pos;
	C2D part;
	S2D targ;
	int nb_particle = particle_get_nb();
	particle_get_init_head();
	particle_allow_increment();
	for(int i = 0; i < nb_particle; i++){
		particle_get(NULL, &part, NULL, NULL);
		graphic_particle(part.rayon, part.centre.x, part.centre.y);
	}	
	int nb_robot = robot_get_nb();
	robot_get_init_head();
	robot_allow_increment();
	for(int i = 0; i < nb_robot; i++){
		robot_get(&pos, NULL, &targ, &a, &sel, NULL, NULL);
		graphic_robot(pos.x, pos.y, a, sel);
		#ifdef DEBUG
		if(sel)
			graphic_debug(DEBUG_RAYON, targ.x, targ.y, 1, 0, 0);
		#endif
	}
	graphic_affichage_end();
}



