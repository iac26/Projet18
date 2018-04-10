#ifndef READ_H
#define READ_H

int read_file(char * filename);
void read_save(char * filename);
static int read_robot(	char * line);
static int read_particle(	char * line);
static void remove_comments(char * line);
static int detect_fin_liste(char * line);
static int detect_anything(char * line);
static void reset_str(char * line);
static int read_nb_robot_step(void); 
static int read_robot_step(void); 
static int read_end_robot_step(void); 
static int read_nb_particle_step(void); 
static int read_particle_step(void); 
static int read_end_particle_step(void); 

#endif
