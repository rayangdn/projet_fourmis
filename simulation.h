#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "fourmiliere.h"
#include "food.h"

class Simulation {
public :
	unsigned int get_nb_food() const;
	unsigned int get_ensemble_fourmilieres_size() const;
	unsigned int get_total_food(int) const;
	unsigned int get_nbC(int) const;
	unsigned int get_nbD(int) const;
	unsigned int get_nbP(int) const;
	void lecture(std::string);
	void decodage_ligne(std::string&, bool&);
	void supprimer_structs();
	void draw_simulation(Graphic);
	void initialise_ensemble_couleurs();
	
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmilieres ensemble_fourmilieres;
	Ensemble_couleurs ensemble_couleurs;
};

#endif
