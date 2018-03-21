#ifndef PARTICLE_H
#define PARTICLE_H


typedef struct particle PARTICLE;

int particle_delete_u(unsigned int id);
int particle_delete_i(unsigned int id);
void particle_print(void);
void particle_get(double * e, double * rad, double * x, double * y, unsigned int * i_id, unsigned int * u_id);
void particle_get_init_i(unsigned int id);
void particle_get_init_u(unsigned int id);
unsigned int particle_create(double e, double r, double x, double y);
void particle_set_nb(int nb);
int particle_get_nb(void);


#endif
