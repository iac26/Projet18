#ifndef PARTICLE_H
#define PARTICLE_H


typedef struct particle PARTICLE;

int particle_delete_u(unsigned int id);
int particle_delete_i(unsigned int id);
void particle_print(void);
unsigned int particle_create(double e, double r, double x, double y);


#endif
