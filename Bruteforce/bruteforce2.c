#include <stdio.h>
#include <math.h>
#define EPSIL_ZERO				1e-2
#define EPSIL_ALIGNEMENT		0.0625

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

int main(void) {
	for(double angle = -10.0; angle < 10.0; angle += 0.1) {
		double a = angle;
		util_range_angle(&a);
		printf("%lf -> %lf ",angle, a);
		if((a > -M_PI)&&(a < M_PI)) {
			printf("OK\n");
		} else {
			printf("ERRRRRROOOOOOOR\n");
		}
	}
}




