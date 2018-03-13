#ifndef READ_H
#define READ_H

static int read_file(char * filename);
static void read_robot(	char * line, int * p_robot_count);
static void read_particle(	char * line, int * p_particle_count, int nb_particle, unsigned int line_count);
static void remove_comments(char * line);
static int detect_fin_liste(char * line);
static int detect_anything(char * line);

#endif
