#include <iostream>
#include <vector>
#include <string>

#include "squarecell.h"
#include "error_squarecell.h"



void initialise_grid(Grid& grid, const unsigned int g_max) {
	for(int i(0); i < g_max; i++) {
		grid.push_back(vector<bool>());
		for(int j(0); j < g_max; j++) {
			grid[i].push_back(false);   
		}
	}
}

void test_validation_carre(Grid grid, Carre carre) {
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
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur, grid.size());
		exit(EXIT_FAILURE);
	}
	if (carre.point.y + carre.longeur > grid.size()) {
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur, grid.size());
		exit(EXIT_FAILURE);
	}
}

void initialise_carre(Grid& grid, Carre carre) {
	
	for(size_t i(carre.point.y); i <carre.point.y + carre.longeur ; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

void supprime_carre(Grid& grid, Carre carre) {
	
	for(size_t i(carre.point.y); i <carre.point.y + carre.longeur ; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = false;
		}
	} 
}

bool test_superposition_2_carres(Grid grid, Carre carre, Carre autre_carre) {
	unsigned int compteur(0);
	initialise_carre(grid, carre);
	initialise_carre(grid, autre_carre);
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if(kase == true){
				++compteur;
			}
		}
	}
	if(compteur < carre.longeur*carre.longeur + autre_carre.longeur*autre_carre.longeur) {
		return false;
	}
	return true;
}
bool test_superposition(Grid grid, Carre autre_carre, Ensemble_carre ensemble_carre) {
	unsigned int compteur(0);
	unsigned int compteur_carre(0);
	initialise_carre(grid, autre_carre);
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if(kase == true){
				++compteur;
			}
		}
	}
	//calcul nb carre;
	for(const auto& carre : ensemble_carre) {
		
		compteur_carre += carre.longeur*carre.longeur;
	}
	compteur_carre += autre_carre.longeur*autre_carre.longeur;
	if(compteur < compteur_carre) {
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
