#include "utilitaire.h"
#include "tolerance.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

unsigned short ud = 1;
FILE* f;

void printCirc(char str[100], C2D a, int n) {
	sprintf(str, "Circle %d : x=%lf, y=%lf, r=%lf\n", n, a.centre.x, a.centre.y, a.rayon);
}

void printVec(char str[100], S2D a, int n) {
	sprintf(str, "Vector %d : x=%lf, y=%lf\n", n, a.x, a.y);
}

double util_distance(S2D a, S2D b) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\nDistance:\n");
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	printVec(str, b, 2);
	double dx, dy, dist;
	dx = a.x - b.x;
	dy = a.y - b.y;
	dist = sqrt(dx*dx + dy*dy);
	return dist;
}

double util_angle(S2D a, S2D b) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\nAngle:\n");
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	printVec(str, b, 2);
	fputs(str, f);
	double dx, dy, angle;
	dx = b.x - a.x;
	dy = b.y - a.y;
	angle = atan2(dy, dx);
	util_range_angle(&angle);
	return angle;
}

void util_range_angle(double *p_angle) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\nRange angle %lf\n", *p_angle);
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
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nPoint dehors (max=%lf):\n", max);
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	if((fabs(a.x) > max)||(fabs(a.y) > max)) {
		return true;
	}
	return false;
}

bool util_alpha_dehors(double alpha) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nAngle dehors: %lf \n", alpha);
	if(fabs(alpha) > M_PI) {
		return true;
	}
	return false;
}

bool util_point_dans_cercle(S2D a, C2D c) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nPoint dans cercle:\n");
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	printCirc(str, c, 1);
	fputs(str, f);
	double dist;
	dist = util_distance(a, c.centre);
	if(dist < (c.rayon - EPSIL_ZERO)) {
		return true;
	}
	return false;
}

bool util_collision_cercle(C2D a, C2D b, double *p_dist) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nCollision cercle:\n");
	char str[100];
	printCirc(str, a, 1);
	fputs(str, f);
	printCirc(str, b, 2);
	fputs(str, f);
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
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nDeplacement (angle=%lf, dist=%lf)\n", alpha, dist);
	char str[100];
	printVec(str, p, 1);
	fputs(str, f);
	S2D new_p;
	new_p.x = p.x + dist*cos(alpha);
	new_p.y = p.y + dist*sin(alpha);
	return new_p;
}

bool util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\nEcart angle (alpha=%lf)\n", alpha);
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	printVec(str, b, 2);
	fputs(str, f);
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
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nAlignement (alpha=%lf)\n", alpha);
	char str[100];
	printVec(str, a, 1);
	fputs(str, f);
	printVec(str, b, 2);
	fputs(str, f);
	double angle;
	if(util_ecart_angle(a, alpha, b, &angle)) {
		if(fabs(angle) < EPSIL_ALIGNEMENT) {
			return true;
		}
	}
	return false;
}

bool util_inner_triangle(double la, double lb, double lc, double lb_new, double *p_la_new) {
	if(ud) {
		f = fopen("data.txt", "w");
		ud = 0;
	} else {
		f = fopen("data.txt", "a");
	}
	fprintf(f, "\n\nInner triangle: la=%lf, lb=%lf, lc=%lf, lb_new=%lf\n", la, lb, lc, lb_new);
	double a, b, c, delta, s1, s2;
	if(	(la > EPSIL_ZERO)&&(lb >= 0)&&(lc > EPSIL_ZERO)&&
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


