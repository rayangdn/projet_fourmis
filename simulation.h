

#include "fourmiliere.h"
#include "food.h"

class Simulation {
	public :
	Simulation(Grid);
	~Simulation() {};
	void lecture(char *);
	void decodage_ligne(std::string);
	private :
	Grid grid;
	Ensemble_food ensemble_food;
	Ensemble_fourmiliere ensemble_fourmiliere;
	
};


