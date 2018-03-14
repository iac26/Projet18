#ifndef ROBOT_H
#define ROBOT_H

static typedef struct {
	double x;
	double y;
	double a;
}ROBOT;

ROBOT ** robot_init(int nb_robot);
void robot_delete_all(ROBOT ** list, int nb_robot)
ROBOT * robot_create(double x, double y, double a);


#endif
