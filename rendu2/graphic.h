#ifndef GRAPHIC_H
#define GRAPHIC_H

#define WIDTH 800
#define HEIGHT 800

int graphic_init_glut(int * argc, char ** argv);
void graphic_affichage(void);
void graphic_reshape(int w, int h);
void graphic_robot(double x, double y, double angle);
void graphic_particle(double r, double x, double y);
void graphic_border(void);



#endif
