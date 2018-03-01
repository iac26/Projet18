#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <stdbool.h>
#include "tolerance.h"

typedef struct {
	double x;
	double y;
}S2D;

typedef struct {
	S2D centre;
	double rayon;
}C2D;

double util_distance(S2D a, S2D b);

double util_angle(S2D a, S2D b);

void util_range_angle(double * p_angle);

bool util_point_dehors(S2D a, double max);

bool util_alpha_dehors(double alpha);

bool util_point_dans_cercle(S2D a, C2D c);

bool util_collision_cercle(C2D a, C2D b, double * p_dist);

S2D util_deplacement(S2D p, double alpha, double dist);

bool util_ecart_angle(S2D a, double alpha, S2D b, double * p_ecart_angle);

bool util_alignement(S2D a, double alpha, S2D b);

bool util_inner_triangle(double la, double lb, double lc, double lb_new, double * p_la_new);

#endif
