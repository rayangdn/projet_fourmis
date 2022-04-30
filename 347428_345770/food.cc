//food.cc
//Rayan Gauderon membre1: 40%
//Maxime Luyet membre 2: 60%

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "food.h"

using namespace std;

Food::Food(Carre carre, unsigned int val_food) : carre(carre), val_food(val_food) {}

void Food::initialise_food_on_grid() {
	initialise_carre_centre(carre);
}

void Food::superposition_food() {
	if(test_superposition_sans_coord(carre)) {
		cout << message::food_overlap(carre.point.x,carre.point.y);
		exit(EXIT_FAILURE);
		}
}

void decodage_line_food(string line, Ensemble_food& ensemble_food) {
		istringstream data(line);
		unsigned int x, y;
		data >> x >> y;
		Carre carre{1, {x, y}};
		test_validation_carre_non_centre(carre);
		Food food(carre, val_food);
		food.superposition_food();
		food.initialise_food_on_grid();
		ensemble_food.push_back(food);
}