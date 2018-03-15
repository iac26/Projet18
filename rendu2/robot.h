#ifndef ROBOT_H
#define ROBOT_H

typedef struct robot ROBOT;

int robot_delete_u(unsigned int id);
int robot_delete_i(unsigned int id);
void robot_print(void);

unsigned int robot_create(double x, double y, double a);


#endif
