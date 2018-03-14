#include <stdlib.h>
#include <GLUT/glut.h>

#include <stdio.h>
#include <string.h>
#include <math.h>


#include "graphic.h"

int main(int argc, char ** argv) {
	if(argc > 2) {
		if(!strcmp(argv[1], "Error")) {
			read_file(argv[2]);
		}
		if(!strcmp(argv[1], "Draw")) {
			
		}
	}
	
	
	return EXIT_SUCCESS;
}
