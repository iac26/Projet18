#include <stdio.h>
#include <math.h>

#include "error.h"
#include "constantes.h"

void error_no_error_in_this_file()
{
	printf("Success - No error in this file\n");
}

void error_file_missing(const char file_name[])
{
	printf("Error - File %s is missing\n", file_name);
}

void error_invalid_nb_robots()
{
	printf("Error - Invalid number of robots\n");
}

void error_invalid_robot()
{
	printf("Error - Impossible to read robot data\n");
}

void error_invalid_robot_angle(double alpha)
{
	printf("Error - Invalid robot angle %f\n",alpha);
	printf("alpha must be in [%lf ; %lf]\n",-M_PI, M_PI);
}

void error_fin_liste_robots(unsigned int line_number)
{
	printf("Error - Unexpected \"FIN_LISTE\" "
		   "in robot list on line %u\n", line_number);
}

void error_missing_fin_liste_robots(unsigned int line_number)
{
	printf("Error - Missing \"FIN_LISTE\" in robot list"
			" on line %u\n",line_number);
}

void error_invalid_nb_particules()
{
	printf("Error - Invalid number of particules\n");
}

void error_invalid_particule()
{
	printf("Error - Impossible to read particule data\n");
}

void error_invalid_particule_value(double energy, double radius,
								   double x0, double y0)
{
	printf("Error - Invalid particule informations %f %f %f %f \n",
		   energy, radius, x0, y0);
	printf("x0 and y0 must be in [%d ; %d]\n", -DMAX, DMAX);
	printf("energy must be in [0 ; %d]\n", E_PARTICULE_MAX);
	printf("radius must be in [%g ; %d]\n", R_PARTICULE_MIN, 
											R_PARTICULE_MAX);
}

void error_fin_liste_particules(unsigned int line_number)
{
	printf("Error - Unexpected \"FIN_LISTE\" in particule list"
		   " on line %u\n", line_number);
}

void error_missing_fin_liste_particules(unsigned int line_number)
{
	printf("Error - Missing \"FIN_LISTE\" in particules list"
			" on line %u\n",line_number);
}

void error_useless_char(unsigned int line_number)
{
	printf("Error - Incorrect line format for line %u\n", line_number);
}

void error_collision(ERROR_COLLISION type, 
				     unsigned int id1, unsigned int id2)
{
	unsigned int tmp;
	char * names[] = {"Robot", "Particule"};
	char * types[] = {"ROBOT-ROBOT", "ROBOT-PARTICULE", 
					  "PARTICULE-PARTICULE"};
	char * name_col[] = {names[0], names[1]};
	
	if(type == ROBOT_ROBOT)
		name_col[1] = names[0];
	else if(type == PARTICULE_PARTICULE)
		name_col[0] = names[1];
	
	if(type != ROBOT_PARTICULE && id1 > id2)
	{
		tmp = id2;
		id2 = id1;
		id1 = tmp;
	}
	
	printf("There is a %s collision between:\n", types[type]);
	printf("%s %d and %s %d\n", name_col[0], id1, name_col[1], id2);
}
