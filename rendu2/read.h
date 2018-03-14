#ifndef READ_H
#define READ_H

int read_file(char * filename);
static void read_robot(	char * line, int * p_robot_count);
static void read_particle(	char * line, int * p_particle_count);
static void remove_comments(char * line);
static int detect_fin_liste(char * line);
static int detect_anything(char * line);

#endif
