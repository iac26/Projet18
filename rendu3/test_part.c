#include <stdio.h>
#include <stdlib.h>
#include "particle.h"

int main() {
	particle_create(0.1, 0.1, 10, 10);
	particle_create(0.1, 0.1, 10, 10);
	particle_create(0.1, 0.2, 10, 10);
	particle_create(0.1, 0.1, 10, 10);
	particle_create(0.1, 0.3, 10, 10);
	particle_create(0.1, 0.1, 10, 10);
	particle_create(0.1, 0.1, 10, 10);
	particle_create(0.1, 0.5, 10, 10);
	particle_create(0.1, 0.5, 10, 10);
	particle_create(0.1, 0.5, 10, 10);
	particle_create(0.1, 0.5, 10, 10);
	particle_create(0.1, 0.9, 10, 10);
	particle_create(0.1, 0.9, 10, 10);
	particle_create(0.1, 0.3, 10, 10);
	particle_create(0.1, 0.1, 10, 10);
	particle_print();
	particle_delete_u(5);
	particle_delete_u(8);
	particle_delete_u(2);
	particle_print();
	
	
}
