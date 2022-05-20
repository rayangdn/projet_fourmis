#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "fourmiliere.h"
#include "food.h"

class Simulation {
public :
	unsigned int get_nb_food() const;
	unsigned int get_nb_fourmiliere () const;
	double get_total_food(int) const;
	unsigned int get_nbC(int) const;
	unsigned int get_nbD(int) const;
	unsigned int get_nbP(int) const;
	void lecture(std::string);
	bool decodage_line(std::string&);
	void supprimer_structs();
	void ecriture_fichier(std::ofstream&) const;
	void draw_simulation();
	void refresh();
	void maj_fourmiliere(unsigned int i);
	void fourmis_kill(unsigned int i);
private :
	Ensemble_food ensemble_food;
	Ensemble_fourmilieres ensemble_fourmilieres;
	void create_food();
	bool superposition_food_with_all(const Carre&);
	bool test_expend_fourmiliere(unsigned int);
	
};

#endif
