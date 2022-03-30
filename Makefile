# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = squarecell.cc error_squarecell.cc prog.cc simulation.cc message.cc  food.cc fourmiliere.cc fourmis.cc
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o prog

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
squarecell.o: squarecell.cc squarecell.h error_squarecell.h
error_squarecell.o: error_squarecell.cc error_squarecell.h
prog.o: prog.cc simulation.h message.h food.h constantes.h squarecell.h
simulation.o: simulation.cc simulation.h message.h food.h constantes.h \
  squarecell.h
message.o: message.cc message.h
food.o: food.cc food.h constantes.h squarecell.h
fourmiliere.o: fourmiliere.cc
