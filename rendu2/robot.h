#ifndef ROBOT_H
#define ROBOT_H

#include "utilitaire.h"

typedef struct robot ROBOT;

int robot_delete(unsigned int id);
void robot_print(void);
unsigned int robot_create(double x, double y, double a);


#endif
