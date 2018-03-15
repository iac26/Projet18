#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "read.h"
#include "robot.h"
#include "particle.h"
#include "model.h"


int main(int argc, char ** argv) {
	
	if (argc > 1) {
		if(read_file(argv[1])) {
			robot_print();
			particle_print();
			model_collisions();
		}
	}
	
	
	
	return EXIT_SUCCESS;
}

