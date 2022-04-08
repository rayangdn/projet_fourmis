#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "fourmiliere.h"
#include "food.h"

class Simulation {
public :
	bool lecture(char *);
	void decodage_ligne(std::string, bool&);
	void supprimer_structs();
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmiliere ensemble_fourmiliere;
};

#endif
