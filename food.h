#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "constantes.h"
#include "squarecell.h"
#include "message.h"

class Food {
public :
	Food(Carre);
	~Food() {};
	Carre get_carre() const;
	void initialise_food_on_grid();
	bool superposition_food();
	void ecriture_food(std::ofstream&) const;
	void draw_food();
	void random_food();
private :
	Carre carre;
};

typedef std::vector<Food> Ensemble_food;

bool decodage_line_food(std::string, Ensemble_food&);

#endif
