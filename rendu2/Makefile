#Makefile

OFILES=error.o read.o 

all : main.x

main.x : $(OFILES)
	gcc $(OFILES) -o $@

error.o : error.c error.h constantes.h
	gcc -c $< -o $@
	
read.o : read/read.c read/read.h error.h constantes.h
	gcc -c $< -o $@
