#Makefile

OFILES=main.o robot.o error.o read.o particle.o utilitaire.o model.o graphic.o
CFILES=main.cpp robot.c error.c read.c particle.c utilitaire.c model.c graphic.c
CC=gcc
CFLAGS=-Wall
LIB= -lGL -lglut -lglui -lm -lstdc++
LIB_MAC= -framework GLUT -framework OpenGL -framework Cocoa -lglui -lm -lstdc++

all : projet.x

mac : $(OFILES)
	$(CC) $(OFILES) -o projet.x $(LIB_MAC)
	@rm -f *.o

projet.x : $(OFILES)
	$(CC) $(OFILES) -o $@ $(LIB)
	@rm -f *.o
	
clean : 
	@echo "CLEANING"
	@rm -f *.o
	
depend : 
	@echo "UPDATING DEPENDENCIES"
	@(sed '/^# DEPENDANCES/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

# DEPENDANCES
main.o: main.cpp read.h robot.h particle.h model.h graphic.h constantes.h \
  tolerance.h
robot.o: robot.c utilitaire.h tolerance.h robot.h constantes.h
error.o: error.c error.h constantes.h tolerance.h
read.o: read.c read.h error.h robot.h particle.h constantes.h tolerance.h \
  utilitaire.h
particle.o: particle.c utilitaire.h tolerance.h particle.h constantes.h
utilitaire.o: utilitaire.c utilitaire.h tolerance.h
model.o: model.c utilitaire.h tolerance.h error.h constantes.h robot.h \
  particle.h model.h
graphic.o: graphic.c utilitaire.h tolerance.h graphic.h constantes.h
