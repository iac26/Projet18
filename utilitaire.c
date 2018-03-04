#include "utilitaire.h"
#include "tolerance.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

double util_distance(S2D a, S2D b) {
	double dx, dy, dist;
	dx = a.x - b.x;
	dy = a.y - b.y;
	dist = sqrt(dx*dx + dy*dy);
	return dist;
}

double util_angle(S2D a, S2D b) {
	double dx, dy, angle;
	dx = a.x - b.x;
	dy = a.y - b.y;
	angle = atan2(dy, dx);
	util_range_angle(&angle);
	return angle;
}

void util_range_angle(double *p_angle) {
	if(p_angle) {
		if(*p_angle > M_PI) {
			*p_angle -= 2.0*M_PI;
		}
		else if(*p_angle <= -M_PI) {
			*p_angle += 2.0*M_PI;
		}
	}
}

bool util_point_dehors(S2D a, double max) {
	if((fabs(a.x) > max)||(fabs(a.y) > max)) {
		return true;
	}
	return false;
}

bool util_alpha_dehors(double alpha) {
	if(fabs(alpha) > M_PI) {
		return true;
	}
	return false;
}

bool util_point_dans_cercle(S2D a, C2D c) {
	double dx, dy, dist;
	dx = a.x - c.centre.x;
	dy = a.y - c.centre.y;
	dist = sqrt(dx*dx + dy*dy);
	if(dist < (c.rayon - EPSIL_ZERO)) {
		return true;
	}
	return false;
}

bool util_collision_cercle(C2D a, C2D b, double *p_dist) {
	double dist;
	dist = util_distance(a.centre, b.centre);
	if(p_dist) {
		*p_dist = dist;
	}
	if(dist < (a.rayon + b.rayon - EPSIL_ZERO)) {
		return true;
	}
	return false;
}

S2D util_deplacement(S2D p, double alpha, double dist) {
	S2D temp;
	temp.x = p.x + dist*cos(alpha);
	temp.y = p.y + dist*sin(alpha);
	return temp;
}

bool util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle) {
	double dx, dy, dist2;
	dx = a.x - b.x;
	dy = a.y - b.y;
	dist2 = dx*dx + dy*dy;
	if(dist2 > EPSIL_ZERO*EPSIL_ZERO) {
		if(p_ecart_angle) {
			*p_ecart_angle = atan2(dy, dx) - alpha;
			util_range_angle(p_ecart_angle);
		}
		return true;
	}
	return false;
}

bool util_alignement(S2D a, double alpha, S2D b) {
	double angle;
	if(util_ecart_angle(a, alpha, b, &angle)) {
		if(fabs(angle) < EPSIL_ALIGNEMENT) {
			return true;
		}
	}
	return false;
}

bool util_inner_triangle(double la, double lb, double lc, double lb_new, double *p_la_new) {
	double a, b, c, delta, s1, s2;
	if(	(la > EPSIL_ZERO)&&(lb > EPSIL_ZERO)&&(lc > EPSIL_ZERO)&&
		(lb_new >= lb)&&(lb_new <= lc)) {
		a = 1.0;
		b = -2.0*lc*(la*la + lc*lc - lb*lb)/(2.0*la*lc);
		c = lc*lc - lb_new*lb_new;
		delta = b*b - 4.0*a*c;
		s1 = (-b + sqrt(delta))/2.0*a;
		s2 = (-b - sqrt(delta))/2.0*a;
		if((s1 < la)&&(s1 > 0.0)) {
			if(p_la_new)
				*p_la_new = s1;
		} else {
			if(p_la_new)
				*p_la_new = s2;
		}
		return true;
	} else {
		return false;
	}
	
}


