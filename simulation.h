#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "fourmiliere.h"
#include "food.h"

class Simulation {
public :
	bool lecture(char *);
	void decodage_ligne(std::string, bool&);
	void supprimer_structs();
	void draw_simulation(Graphic);
	void initialise_ensemble_couleurs();
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmilieres ensemble_fourmilieres;
	Ensemble_couleurs ensemble_couleurs;
};

#endif
