#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "constantes.h"
#include "squarecell.h"
#include "message.h"

class Food {
public :
	Food(Carre, unsigned int);
	~Food() {};
	void initialise_food_on_grid();
	void superposition_food(bool&);
	void draw_food(Graphic);
private :
	Carre carre;
	unsigned int val_food;
};

typedef std::vector<Food> Ensemble_food;

void decodage_line_food(std::string, Ensemble_food&, bool&);

#endif
