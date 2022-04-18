#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "fourmiliere.h"
#include "food.h"

class Simulation {
public :
	bool lecture(std::string);
	void decodage_ligne(std::string&, bool&);
	void supprimer_structs();
	void draw_simulation(Graphic);
	void initialise_ensemble_couleurs();
	unsigned int get_Nb_food() const;
	unsigned int get_ensemble_fourmilieres_size() const;
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmilieres ensemble_fourmilieres;
	Ensemble_couleurs ensemble_couleurs;
};

#endif
