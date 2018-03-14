#ifndef PARTICLE_H
#define PARTICLE_H

static typedef struct {
	double e;
	double r;
	double x;
	double y;
}PARTICLE;

PARTICLE * particle_create(double e, double r, double x, double y);


#endif
