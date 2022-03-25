#include <iostream>
#include "squarecell.h"
#include "message.h"
#include "food.h"
#include "constantes.h"
class Simulation {
	public :
	Simulation(Grid, Ensemble_carre);
	void lecture(char * mon_fichier);
	void decodage_ligne(std::string line);
	private :
	Grid grid;
	Ensemble_carre ensemble_carre;
};

