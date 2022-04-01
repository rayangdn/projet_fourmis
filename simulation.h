
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "fourmiliere.h"
#include "food.h"

class Simulation {
	public :
	void lecture(char *);
	void decodage_ligne(std::string);
	private :
	Ensemble_food ensemble_food;
	Ensemble_fourmiliere ensemble_fourmiliere;
};


