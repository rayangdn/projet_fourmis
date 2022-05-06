//food.cc
//Rayan Gauderon membre1: 40%
//Maxime Luyet membre 2: 60%

#include <iostream>
#include <fstream>
#include <random>

#include "food.h"

using namespace std;

const int MIN_FOOD = 1;
const int MAX_FOOD = g_max-2;

Food::Food(Carre carre, unsigned int val_food) : carre(carre), val_food(val_food) {}

Carre Food::get_carre() const {
	return carre;
}

void Food::initialise_food_on_grid() {
	initialise_carre_centre(carre);
}

bool Food::superposition_food() {
	if(test_superposition_sans_coord(carre)) {
		cout << message::food_overlap(carre.point.x,carre.point.y);
		return true;
	}
	return false;
}

void Food::ecriture_food(ofstream& fichier) const {
	fichier << to_string(carre.point.x) << " " << to_string(carre.point.y) << "\n";
}

void Food::draw_food() {
	unsigned int style(LOSANGE);
	unsigned int couleur(WHITE);
	draw_carre(carre, style,  couleur);
}

void Food::random_food() {
	random_device rd;
    uniform_int_distribution<int> distr(MIN_FOOD, MAX_FOOD);
    default_random_engine eng(rd());
    carre.point.x = distr(eng);
    carre.point.y = distr(eng);
}

bool decodage_line_food(string line, Ensemble_food& ensemble_food) {
	istringstream data(line);
	unsigned int x, y;
	data >> x >> y;
	Carre carre{1, {x, y}};
	Food food(carre, val_food);
	if(test_validation_carre_no_bound(carre)) {
		return true;
	}
	if(food.superposition_food()) {
		return true;
	}
	food.initialise_food_on_grid();
	ensemble_food.push_back(food);
	return false;
}
