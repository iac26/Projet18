#ifndef ROBOT_H
#define ROBOT_H

typedef struct robot ROBOT;

int robot_delete_u(unsigned int id);
int robot_delete_i(unsigned int id);
void robot_delete_all(void);
void robot_print(void);
void robot_get_init_i(unsigned int id);
void robot_get_init_u(unsigned int id);
void robot_get(double * x, double * y, double * angle, unsigned int * i_id, unsigned int * u_id);
unsigned int robot_create(double x, double y, double a);
void robot_set_nb(int nb);
int robot_get_nb(void);


#endif
