#Makefile

OFILES_T=test.o robot.o error.o read.o particle.o utilitaire.o model.o graphic.o
CC=gcc
LIB=-lglui -lglut -framework OpenGL -framework Cocoa

all : test.x

test.x : $(OFILES_T)
	$(CC) $(OFILES_T) -o $@ $(LIB)
	
test.o : main.cpp robot.h read.h model.h graphic.h
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
	
graphic.o : graphic.c graphic.h constantes.h utilitaire.h
	$(CC) -c $< -o $@
