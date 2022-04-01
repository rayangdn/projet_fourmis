#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "squarecell.h"
#include "message.h"

class Food {
	public :
	Food(Carre, unsigned int);
	~Food() {};
	void initialise_food_on_grid(Grid&);
	void test_superposition_food(Grid&);
	
	private :
	Carre carre;
	unsigned int val_food;
	
	

};
typedef vector<Food> Ensemble_food;

void decodage_line_food(std::string, Grid&, Ensemble_food&);

#endif
