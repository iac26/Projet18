#Makefile

OFILES=main.o robot.o error.o read.o particle.o utilitaire.o simulation.o graphic.o
CFILES=main.cpp robot.c error.c read.c particle.c utilitaire.c simulation.c graphic.c
CC=gcc
CFLAGS=-Wall -g
LIB= -lGL -lglut -lglui -lm -lstdc++
LIB_MAC= -framework GLUT -framework OpenGL -framework Cocoa -lglui -lm -lstdc++

all : projet.x

mac : $(OFILES)
	$(CC) $(OFILES) -o projet.x $(LIB_MAC)
	
test : test_part.o	particle.o utilitaire.o
	$(CC) test_part.o particle.o -o test.x
	
test_part.o : test_part.c particle.h utilitaire.h

projet.x : $(OFILES)
	$(CC) $(OFILES) -o $@ $(LIB)
	
clean : 
	@echo "CLEANING"
	@rm -f *.o *.x
	
depend : 
	@echo "UPDATING DEPENDENCIES"
	@(sed '/^# DEPENDANCES/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

# DEPENDANCES
main.o: main.cpp read.h simulation.h utilitaire.h tolerance.h graphic.h \
  constantes.h
robot.o: robot.c utilitaire.h tolerance.h robot.h constantes.h
error.o: error.c error.h constantes.h tolerance.h
read.o: read.c read.h error.h robot.h utilitaire.h tolerance.h particle.h \
  constantes.h
particle.o: particle.c utilitaire.h tolerance.h particle.h constantes.h
utilitaire.o: utilitaire.c utilitaire.h tolerance.h
simulation.o: simulation.c utilitaire.h tolerance.h error.h constantes.h \
  robot.h particle.h simulation.h graphic.h
graphic.o: graphic.c utilitaire.h tolerance.h graphic.h constantes.h
