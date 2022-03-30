#include "food.h"

using namespace std;

Food::Food(Carre carre, unsigned int val_food) : carre(carre), val_food(val_food) {}

void Food::initialise_food_on_grid(Grid& grid) {
	initialise_carre_non_centre(grid, carre);
}

void Food::test_superposition_food(Grid& grid) {
	if(test_superposition(grid, carre)) {
		cout << message::food_overlap(carre.point.x,carre.point.y);
				exit(EXIT_FAILURE);
		}
	initialise_food_on_grid(grid);
}

void decodage_line_food(string line, Grid& grid, Ensemble_food& ensemble_food) {
		istringstream data(line);
		
		unsigned int x, y;
		
		data >> x >> y;
		cout << "Nourriture "  << " : " << x << " " << y << endl;
		Carre carre{1, {x, y}};
		Food food(carre, val_food);
		test_validation_carre(grid, carre);
		food.test_superposition_food(grid);
		ensemble_food.push_back(food);
}
