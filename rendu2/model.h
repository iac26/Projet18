#ifndef MODEL_H
#define MODEL_H


int initial_collisions(void);
static int robot_collision(double * p_dist, unsigned int * p_id_a, unsigned int * p_id_b);
static int particle_collision(double * p_dist, unsigned int * p_id_a, unsigned int * p_id_b);
static int cross_collision(double * p_dist, unsigned int * p_id_a, unsigned int * p_id_b);

#endif
