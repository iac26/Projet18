/* Projet18
 * Version: 0.1
 * Authors: Lianyi Ni & Iacopo Sprenger
 * Date: 01.03.2018
 **/

#include "utilitaire.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

double util_distance(S2D a, S2D b){
	double dx, dy, d;
	dx = a.x - b.x;
	dy = a.y - b.y;
	d = sqrt(dx*dx + dy*dy);
	return d;
}

double util_angle(S2D a, S2D b) {
	double dx, dy, d, *p_angle;
	dx = a.x - b.x;
	dy = a.y - b.y;
	*p_angle = atan(dy/dx);
	return util_range_angle(&p_angle);
}

void util_range_angle(double *p_angle) {
	if(*p_angle > pi) {
		*p_angle += -2*pi;
	}
	else if(*p_angle =< -pi){
		*p_anlge += 2*pi;
	}
}

bool util_point_dehors(S2D a, double max) {
	if((abs(a.x) > max) || (abs(a.y) > max)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

bool util_alpha_dehors(double alpha) {
	if(abs(alpha) > pi) {
		return TRUE;
	} else {
		return FALSE;
	}
}

bool util_point_dans_cercle(S2D a, C2D c) {
	double dx,dy,d;
	dx = a.x - c.centre.x;
	dy = a.y - c.centre.y;
	d = sqrt(dx*dx + dy*dy);
	if(d < c.rayon) {
		return TRUE;
	} else {
		return FALSE;
	}
}

bool util_collision_cercle(C2D a, C2D b, double *p_dist) {
	
}
