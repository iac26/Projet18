# TEST
# Author: Iacopo Sprenger
# Version: 1.1
# Date: 25.02.2018
# Filename: Makefile

CFLAGS=-Wall -w

LIBS=-framework GLUT -framework OpenGL -framework Cocoa

OFILES=test.o utilitaire.o

all : test.x

test.x : $(OFILES)
	gcc $(CFLAGS) $(OFILES) -o $@ $(LIBS)
	
test.o : test.c ../utilitaire.h
	gcc $(CFLAGS) -c $< -o $@
	
utilitaire.o : ../utilitaire.c ../utilitaire.h ../tolerance.h
	gcc $(CFLAGS) -c $< -o $@
	

	

	
clean : 
	@rm -f *.x *.o
	@echo "CLEANED"
