#include "squarecell.h"

void initialise_grid(Grid& grid, const unsigned int g_max) {
	for(size_t i(0); i < g_max; i++) {
		grid.push_back(vector<bool>());
		for(size_t j(0); j < g_max; j++) {
			grid[i].push_back(false);   
		}
	}
}

void test_validation_carre(const Grid& grid, const Carre& carre) {
	if(carre.longeur > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.longeur, grid.size());
		exit(EXIT_FAILURE);
	}
	if(carre.point.x > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.x, grid.size()-1);
		exit(EXIT_FAILURE);
		
	}
	if(carre.point.y > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.y, grid.size()-1);
		exit(EXIT_FAILURE);
	}
	if(carre.point.x + carre.longeur > grid.size()){
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur, grid.size()-1);
		exit(EXIT_FAILURE);
	}
	if (carre.point.y + carre.longeur > grid.size()) {
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur, grid.size()-1);
		exit(EXIT_FAILURE);
	}
}

void initialise_carre_non_centre(Grid& grid,const Carre& carre) {
	
	for(size_t i(carre.point.y); i <carre.point.y + carre.longeur ; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

void initialise_carre_centre(Grid& grid,const Carre& carre) {
	
	for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

void supprime_carre_non_centre(Grid& grid,const Carre& carre) {
	
	for(size_t i(carre.point.y); i <carre.point.y + carre.longeur ; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = false;
		}
	} 
}

void supprime_carre_centre(Grid& grid,const Carre& carre) {
for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

bool test_superposition_2_carres(const Carre& carre,const Carre& autre_carre) {
	if (carre.point.x < autre_carre.point.x + autre_carre.longeur and
		carre.point.x + carre.longeur > autre_carre.point.x and
		carre.point.y < autre_carre.point.y + autre_carre.longeur and
		carre.longeur + carre.point.y > autre_carre.point.y) {
		return true;
   }
   return false;
}

bool test_superposition(const Grid& grid, const Carre& carre) {
	for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				return true;
			
			}
		}
	}
	return false;	
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

