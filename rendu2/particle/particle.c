#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utilitaire.h"
#include "particle.h"
#include "constantes.h"

PARTICLE * particle_create(double e, double r, double x, double y) {
	PARTICLE * p = malloc(sizeof(PARTICLE));
	if(p) {
		p->e = e;
		p->r = r;
		p->x = x;
		p->y = y;
	}
	return p;
}
