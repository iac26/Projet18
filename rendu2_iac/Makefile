# Compilateur a utiliser :
##########################

CC     = gcc

# Options de compilation : (-g = pour deverminer)
#################################################

CFLAGS = -g -Wall

# Repertoire include :
#########################

#INCLUDE_DIR   = /usr/local/include/

# Librairies a utiliser :
#########################

LIBS   = -lglut -lGL -lGLU -lm -Llib -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi

# Liste de fichiers source (.c) a compiler :
############################################

CFILES = robot.c particle.c write.c

# Liste de modules objets (generee a partir de CFILES) :
########################################################

OFILES = $(CFILES:.c=.o)

# Nom du fichier executable :
#############################

CIBLE  = 19_0.x

# edition de liens (rassembler tous les objets -> executable)
#############################################################

$(CIBLE): $(OFILES)
	$(CC) $(OFILES) ${LIBS} -o $(CIBLE)


# compilation separee (production du module objet seulement)

19_0.o: 19_0.c
	$(CC) -c 19_0.c $(CFLAGS)




# Definitions de cibles particulieres :
#
# "make depend" : genere la liste des dependances
# "make clean"  : efface les fichiers .o et .x
#################################################

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x

#
# -- Regles de dependances generees par "make depend"
#####################################################
# DO NOT DELETE THIS LINE
