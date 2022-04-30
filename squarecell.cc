//squarecell.cc
//Rayan Gauderon Membre 1: 75%
//Maxime Luyet Membre 2: 25%

#include <iostream>
#include <vector>

#include "squarecell.h"

using namespace std;

void supprimer_grid() {
	grid.clear();
}

void initialise_grid(const unsigned int& g_max) {
	for(size_t i(0); i < g_max; ++i) {
		grid.push_back(vector<bool>());
		for(size_t j(0); j < g_max; ++j) {
			grid[i].push_back(false);   
		}
	}
}

bool test_validation_carre_non_centre(const Carre& carre) {
	if(carre.point.x > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.x, grid.size()-1);
		return true;
	}
	if(carre.point.y > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.y, grid.size()-1);
		return true;
	}
	if(carre.point.x + carre.longeur > grid.size()){
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur,
		grid.size()-1);
		return true;
	}
	if (carre.point.y + carre.longeur > grid.size()) {
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur,
		grid.size()-1);
		return true;
	}
	return false;
}

bool test_validation_carre_centre(const Carre& carre) {
	if(carre.point.x > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.x, grid.size()-1);
		return true;
	}
	if(carre.point.y > (grid.size()-1)) {
		cout << error_squarecell:: print_index(carre.point.y, grid.size()-1);
		return true;
	}
	if(carre.point.x + (carre.longeur/2) > grid.size()){
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur,
		grid.size()-1);
		return true;
	}
	if (carre.point.y + (carre.longeur/2) > grid.size()) {
		cout << error_squarecell::print_outside(carre.point.x, carre.longeur,
		grid.size()-1);
		return true;
	}
	return false;
}
	
bool test_validation_carre_no_bound(const Carre& carre) {
	if(carre.point.x == 0 or  carre.point.x == g_max-1) {
		cout << "coordinate " << carre.point.x << " does not belong to ] 0, "
		 << g_max-1 << " [\n";
		//food pas le droit d'être sur la bordure
		return true;
	}
	if(carre.point.y == 0 or carre.point.y == g_max-1) {
		cout << "coordinate " << carre.point.x << " does not belong to ] 0, "
		 << g_max-1 << " [\n";
		return true;
	}
	return false;
}
void initialise_carre_non_centre(const Carre& carre) {
	for(size_t i(carre.point.y); i < carre.point.y + carre.longeur ; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

void initialise_carre_centre(const Carre& carre) {
	for(size_t i(carre.point.y-carre.longeur/2);
		i < carre.point.y+carre.longeur/2+1; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2);
			j < carre.point.x + (carre.longeur/2+1); ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

void supprime_carre_non_centre(const Carre& carre) {
	for(size_t i(carre.point.y); i < carre.point.y + carre.longeur; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = false;
		}
	} 
}

void supprime_carre_centre(const Carre& carre) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2);
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
			grid[grid.size()-1-i][j] = true;
		}
	}
}

bool test_superposition_2_carres(const Carre& carre, const Carre& autre_carre) {
	if ((carre.point.x < autre_carre.point.x + autre_carre.longeur) and
		(carre.point.x + carre.longeur > autre_carre.point.x) and
		(carre.point.y < autre_carre.point.y + autre_carre.longeur) and
		(carre.longeur + carre.point.y > autre_carre.point.y)) {
		return true;
   }
   return false;
}

bool test_superposition_avec_coord(const Carre& carre, unsigned int& x,
unsigned int& y) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); 
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				x = j;
				y = i;
				return true;
			}
		}
	}
	return false;	
}

bool test_superposition_sans_coord(const Carre& carre) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); 
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				return true;
			}
		}
	}
	return false;	
}

void draw_carre_losange(const Carre& carre, Graphic graphic) {
	 graphic.draw_carre_losange(carre.point.x, carre.point.y, carre.longeur );
}

void draw_carre_vide(const Carre& carre, Graphic graphic, Couleur couleur) {
	 graphic.draw_carre_vide(carre.point.x, carre.point.y, carre.longeur, couleur);
}

void draw_carre_uniforme(const Carre& carre, Graphic graphic, Couleur couleur) {
	graphic.draw_carre_uniforme(carre.point.x-carre.longeur/2,
	carre.point.y-carre.longeur/2, carre.longeur, couleur); //centrer le carre
}

void draw_carre_diagonale(const Carre& carre, Graphic graphic, Couleur couleur) {
	graphic.draw_carre_diagonale(carre.point.x-carre.longeur/2,
	carre.point.y-carre.longeur/2, carre.longeur, couleur);
}

void draw_carre_grille(const Carre& carre, Graphic graphic, Couleur couleur) {
	graphic.draw_carre_grille(carre.point.x-carre.longeur/2,
	carre.point.y-carre.longeur/2, carre.longeur, couleur);
}

