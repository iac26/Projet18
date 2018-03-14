#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utilitaire.h"
#include "robot.h"
#include "constantes.h"

/* this will be a class style saving method!
 * the user will ask for the creation of a robot and the program will return its adress in memory.
 * with the adress the user will be able to use the robots methods etc...
 * */
 
ROBOT ** robot_init(int nb_robot) {
	return malloc(sizeof(ROBOT *) * nb_robot);
}
 
ROBOT * robot_create(double x, double y, double a) {
	ROBOT * r = malloc(sizeof(ROBOT));
	if(r) {
		r->x = x;
		r->y = y;
		r->a = a;
	}
	return r;
}

void robot_delete_all(ROBOT ** list, int nb_robot) {
	for(int i = 0; i < nb_robot; i++) {
		free(*(list+i)); 
	}
	free(list);
}


