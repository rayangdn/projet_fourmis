#include <iostream>
#include <vector>

//#include "Code_source/error_squarecell.h"

using namespace std;

typedef vector<vector<unsigned int>> Grille; // necessité??
// mettre en unsigned int??
typedef vector<vector<bool>> Grid;
struct Point {
	unsigned int x;
	unsigned int y;
};
/*struct Carre {
	Carre_ carre_;
	Point point;
};
	 mieux comme ça?? pls besoin appel de point dans les fcts
*/

void initialise_grid(Grid& grid, const unsigned int g_max);

void test_validation_carre(Grid grid, Point point, unsigned int carre);

void initialise_carre(Grid& grid, Point point, unsigned int carre);

void supprimer_carre(Grid& grid, Point point, unsigned int carre);

bool test_superposition(Grid& grid, Point point, Point autre_point, unsigned int carre, unsigned int autre_carre);
// faire un vecteur de carre, vecteur de point??

void affiche_grid(Grid grid);


int main() {
	const unsigned int g_max(20);
	Grid grid;
	unsigned int carre(5); // appelé depuis main dans projet??
	Point point{13, 10};
	unsigned int carre1(4);
	Point point1{10, 10};
	
	initialise_grid(grid, g_max);
	test_validation_carre(grid, point, carre);
	initialise_carre(grid, point, carre);
	initialise_carre(grid, point1, carre1);
	
	test_superposition(grid, point, point1, carre, carre1);
	
	affiche_grid(grid);
	return 0;
} 

void initialise_grid(Grid& grid, const unsigned int g_max) {
	for(int i(0); i < g_max; i++) {
		grid.push_back(vector<bool>());
		for(int j(0); j < g_max; j++) {
			grid[i].push_back(false);   
		}
	}
}

void test_validation_carre(Grid grid, Point point, unsigned int carre) {
	if(carre > (grid.size()-1)) {
		cout << ".";
		exit(0);
	}
	if(point.x > (grid.size()-1)) {
		//cout << print_index( point.x, grid.size());// marche pas pq?
		//std::exit(EXIT_FAILURE); //ca fait quoi??
		cout <<".";
		exit(0);
	}
	if(point.y > (grid.size()-1)) {
		cout << ".";
		exit(0);
	}
	for(size_t i(0); i < grid.size(); ++i) {
		for(size_t j(0); j < grid[i].size(); ++j) {
			if( j == point.x and i == grid.size()-1-point.y) {
				if (((carre + point.y) > (grid.size()-1))
					or ((carre + point.x) > (grid[i].size()-1))) {
						 cout << "No succes square";
						 exit(0);		 //message error_squarecell
				}
			}
		}
	 }
}

void initialise_carre(Grid& grid, Point point, unsigned int carre) {
	
	for(size_t i(0); i < grid.size(); ++i) {
		for(size_t j(0); j < grid[i].size(); ++j) {
			if( j == point.x and i == grid.size()-point.y) {
				for(int k(0); k < carre; ++k) {
					for(int l(0); l < carre; ++l) {
						grid[grid.size()-point.y-carre+k][point.x+l] = true;
					}
				}
			}
		}
	}
}

void supprimer_carre(Grid& grid, Point point, unsigned int carre) {
	
	for(size_t i(0); i < grid.size(); ++i) {
		for(size_t j(0); j < grid[i].size(); ++j) {
			if( j == point.x and i == grid.size()-point.y) {
				for(int k(0); k < carre ; ++k) {
					for(size_t l(0); l < carre; ++l) {
						grid[grid.size()-point.y-carre+k][point.x+l] = false;
					}
				}
			}
		}
	}
}

bool test_superposition(Grid& grid, Point point, Point autre_point, unsigned int carre, unsigned int autre_carre) {
	unsigned int compteur(0);
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if(kase == true){
				compteur += 1;
			}
		}
	}
	if ( compteur < (carre*carre + autre_carre *autre_carre)) {
		supprimer_carre(grid, autre_point, autre_carre);
		initialise_carre(grid, point, carre); // good?
		return false;
	}
	return true;
}

void affiche_grid(Grid grid) {
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if( kase == false) {
				cout << "|___";
			} else if ( kase == true) {
				cout << "|_X_";
			}
		}
		cout << endl;
	}
}

