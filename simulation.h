#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <fstream>

#include "fourmiliere.h"
#include "food.h"


class Simulation {
public :
	unsigned int get_nb_food() const;
	unsigned int get_nb_fourmiliere () const;
	unsigned int get_total_food(int) const;
	unsigned int get_nbC(int) const;
	unsigned int get_nbD(int) const;
	unsigned int get_nbP(int) const;
	void lecture(std::string);
	bool decodage_line(std::string&);
	void supprimer_structs();
	void draw_simulation(Graphic);
	void initialise_ensemble_couleurs();
	void ecriture_fichier(std::ofstream&) const;
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmilieres ensemble_fourmilieres;
	Ensemble_couleurs ensemble_couleurs;
};

#endif
