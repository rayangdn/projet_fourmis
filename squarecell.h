#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> Grid;
struct Point {
	unsigned int x;
	unsigned int y;
};
struct Carre {
	unsigned int longeur;
	Point point;
};
typedef vector<Carre> Ensemble_carre;

void initialise_grid(Grid& grid, const unsigned int g_max);

void test_validation_carre(Grid grid, Carre carre);

void initialise_carre(Grid& grid, Carre carre);

void supprimer_carre(Grid& grid, Carre carre);

bool test_superposition_2_carres(Grid grid, Carre carre, Carre autre_carre);

bool test_superposition(Grid grid, Carre autre_carre, Ensemble_carre ensemble_carre);

void affiche_grid(Grid grid);
