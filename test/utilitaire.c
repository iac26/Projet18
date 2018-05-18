/*!
 \file utilitaire.c
 \brief Module qui gère les types concret suivants:
		-> S2D : structure pour mémoriser un point ou un vecteur 2D
		-> C2D : structure pour mémoriser un cercle avec son centre (S2D) et son rayon
		-> on peut ré-utiliser ces fonctions pour son projet
		-> on peut ajouter d'autres fonctions de BAS-NIVEAU
		-> il ne faut PAS introduire de dépendance vis à vis du niveau supérieur du
		   modèle, par exemple en faisant un include de constantes.h
 \author PROG II
 \version 1.01 / version publique
 \date 27 mars 2018
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "utilitaire.h"

double util_distance(S2D a, S2D b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double util_angle(S2D a, S2D b)
{	
	return atan2(b.y - a.y, b.x - a.x);
}

void util_range_angle(double * p_angle)
{
	assert(p_angle);
	
	if(p_angle)
	{	
		while(*p_angle > M_PI) 
			*p_angle -= 2 * M_PI;
			
		while(*p_angle <= -M_PI)
			*p_angle += 2 * M_PI;
	}
}

bool util_point_dehors(S2D a, double max)
{
	return fabs(a.x) > max || fabs(a.y) > max;
}

bool util_alpha_dehors(double alpha)
{
	return fabs(alpha) > M_PI;
}


bool util_point_dans_cercle(S2D a, C2D c)
{
	return util_distance(a, c.centre) < c.rayon - EPSIL_ZERO;
}

bool util_collision_cercle(C2D a, C2D b, double *p_dist)
{
	double d = util_distance(a.centre, b.centre);
	
	if(p_dist)
		*p_dist = d;
		
	return d < (a.rayon + b.rayon) - EPSIL_ZERO;
}


S2D util_deplacement(S2D p, double alpha, double dist)
{
	p.x += dist * cos(alpha);
	p.y += dist * sin(alpha);
	return p;
}

bool util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle)
{
	assert(p_ecart_angle);
	
	if(util_distance(a,b) > EPSIL_ZERO)
	{
	   double angle_cible = util_angle(a,b);
	   double ecart_angle = angle_cible - alpha ;
	   util_range_angle(&ecart_angle);
	   *p_ecart_angle = ecart_angle;
	   return true;
	}
	*p_ecart_angle = 0;
	return false;
}

bool util_alignement(S2D a, double alpha, S2D b)
{
	double ecart_angle = 0.;
	
	if(util_ecart_angle(a, alpha, b, &ecart_angle))
		return fabs(ecart_angle) < EPSIL_ALIGNEMENT;
	else
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
