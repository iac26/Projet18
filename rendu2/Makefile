#Makefile

OFILES_T=test.o robot.o error.o read.o particle.o utilitaire.o model.o
CC=gcc

all : test.x

test.x : $(OFILES_T)
	$(CC) $(OFILES_T) -o $@
	
test.o : test.c robot.h read.h
	$(CC) -c $< -o $@
	
model.o : model.c model.h utilitaire.h robot.h particle.h error.h
	$(CC) -c $< -o $@
	
utilitaire.o : utilitaire.c utilitaire.h tolerance.h
	$(CC) -c $< -o $@
	
error.o : error.c error.h constantes.h
	$(CC) -c $< -o $@
	
read.o : read.c read.h robot.h error.h constantes.h
	$(CC) -c $< -o $@
	
robot.o : robot.c robot.h constantes.h utilitaire.h
	$(CC) -c $< -o $@
	
particle.o : particle.c particle.h constantes.h utilitaire.h
	$(CC) -c $< -o $@
