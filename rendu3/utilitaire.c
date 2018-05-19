/**
 * \file 	utilitaire.c
 * \brief 	fonctions utilitaires de bas niveau
 * \author	Lianyi Ni & Iacopo Sprenger
 * \version 1.1
 */
#include "utilitaire.h"
#include "tolerance.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

double util_distance(S2D a, S2D b) {
	double dx, dy, dist;
	dx = a.x - b.x;
	dy = a.y - b.y;
	dist = sqrt(dx*dx + dy*dy);
	return dist;
}

double util_angle(S2D a, S2D b) {
	double dx, dy, angle;
	dx = b.x - a.x;
	dy = b.y - a.y;
	angle = atan2(dy, dx);
	util_range_angle(&angle);
	return angle;
}

void util_range_angle(double *p_angle) {
	if(p_angle) {
		*p_angle = fmod(*p_angle, 2*M_PI);
		if (*p_angle > M_PI) {
			*p_angle -= 2.0*M_PI;
		} else if (*p_angle <= -M_PI) {
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
	double dist;
	dist = util_distance(a, c.centre);
	if(dist < (c.rayon - EPSIL_ZERO)) {
		return true;
	}
	return false;
}

bool util_collision_cercle(C2D a, C2D b, double * p_dist) {
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
	S2D new_p;
	new_p.x = p.x + dist*cos(alpha);
	new_p.y = p.y + dist*sin(alpha);
	return new_p;
}

bool util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle) {
	double angle, dist;
	dist = util_distance(a, b);
	angle = util_angle(a, b);
	if(dist > EPSIL_ZERO) {
		if(p_ecart_angle) {
			*p_ecart_angle = angle - alpha;
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

bool util_inner_triangle(double la, double lb, double lc, double lb_new,
						 double * p_la_new)
{
	assert(p_la_new);
	
	if (la > EPSIL_ZERO && lb >= 0. && lc > EPSIL_ZERO && // lb peut être nul
	    lb_new >= lb    && lb_new <= lc)
	{
		double l_cosb = (la*la + lc*lc - lb*lb)/(2*la);   // L*cosb

		// par construction l'angle beta est inférieur à pi/2
		// donc lcosb doit être positif 
		assert(l_cosb > 0.);
		
		// coef a,b,c de l'equ du second degré: ax² + bx + c = 0
		//double a = 1.;
		double b = -2*l_cosb ; 
		double c = lc*lc - lb_new*lb_new;
		
		double delta = b*b -4*c ;
	
		if(delta < 0.)			
			return false;
			
		delta = sqrt(delta) / 2;
	
		// solutions: 0.5*( -b +/- sqrt(delta)) doivent être positifs
		// notre solution est la plus petite qui doit être positive
		if( (l_cosb - delta ) < 0.) // erreur numérique: on renvoie 0.
		{
			* p_la_new = 0. ;
			return false;
		}

		* p_la_new = l_cosb - delta ;
	
		return true;
	}
	return false;
}





