#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "read.h"
#include "robot.h"

int main(int argc, char ** argv) {
	
	if (argc > 1) {
		read_file(argv[1]);
	}
	unsigned int a = robot_create(1, 1, 1);
	robot_create(2, 1, 1);
	robot_create(1, 2, 0);
	printf("%u\n", a);
	robot_print();
	robot_delete(a);
	robot_print();
	
	
	return EXIT_SUCCESS;
}
