#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED


#include "squarecell.h"
#include "message.h"

class Food {
public :
	Food(Carre, unsigned int);
	void initialise_food_on_grid();
	void superposition_food();
	
private :
	Carre carre;
	unsigned int val_food;
};

typedef std::vector<Food> Ensemble_food;

void decodage_line_food(std::string, Ensemble_food&);

#endif
