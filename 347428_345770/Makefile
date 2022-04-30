# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc  simulation.cc food.cc fourmiliere.cc fourmis.cc message.cc squarecell.cc error_squarecell.cc     
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o projet

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
projet.o: projet.cc simulation.h fourmiliere.h fourmis.h food.h \
  squarecell.h constantes.h message.h error_squarecell.h
simulation.o: simulation.cc simulation.h fourmiliere.h fourmis.h food.h \
  squarecell.h constantes.h message.h error_squarecell.h
food.o: food.cc food.h squarecell.h constantes.h message.h \
  error_squarecell.h
fourmiliere.o: fourmiliere.cc fourmiliere.h fourmis.h food.h squarecell.h \
  constantes.h message.h error_squarecell.h
fourmis.o: fourmis.cc fourmis.h food.h squarecell.h constantes.h \
  message.h error_squarecell.h
message.o: message.cc message.h
squarecell.o: squarecell.cc squarecell.h constantes.h message.h \
  error_squarecell.h
error_squarecell.o: error_squarecell.cc error_squarecell.h
