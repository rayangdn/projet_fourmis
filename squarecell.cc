//squarecell.cc
//Rayan Gauderon Membre 1: 75%
//Maxime Luyet Membre 2: 25%

#include <iostream>

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
		cout << error_squarecell::print_outside(carre.point.y, carre.longeur,
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
		cout << error_squarecell::print_outside(carre.point.y, carre.longeur,
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

void supprimer_carre_non_centre(const Carre& carre) {
	for(size_t i(carre.point.y); i < carre.point.y + carre.longeur; ++i) {
		for(size_t j(carre.point.x); j < carre.point.x + carre.longeur; ++j) {
			grid[grid.size()-1-i][j] = false;
		}
	} 
}

void supprimer_carre_centre(const Carre& carre) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2);
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
			grid[grid.size()-1-i][j] = false;
		}
	}
}

bool test_superposition_2_carres_non_centre(const Carre& carre, const Carre& autre_carre) {
	if ((carre.point.x < autre_carre.point.x + autre_carre.longeur) and
		(carre.point.x + carre.longeur > autre_carre.point.x) and
		(carre.point.y < autre_carre.point.y + autre_carre.longeur) and
		(carre.point.y + carre.longeur > autre_carre.point.y)) {
		return true;
   }
   return false;
}

bool test_superposition_2_carres_non_centre_centre(const Carre& carre,
												   const Carre& autre_carre) {
													   
	if ((carre.point.x-carre.longeur/2 < autre_carre.point.x + autre_carre.longeur) and 
		(carre.point.x + carre.longeur/2+1 > autre_carre.point.x) and
		(carre.point.y-carre.longeur/2 < autre_carre.point.y + autre_carre.longeur) and
		(carre.point.y + carre.longeur/2+1 > autre_carre.point.y)) {
		return true;
   }
   return false;								   
}												   

bool test_superposition_2_carres_centre(const Carre& carre, const Carre& autre_carre) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); 
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
				if(autre_carre.point.x == j and 
				   autre_carre.point.y == i) {
				return true;
			}
		}
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

bool test_validation_inf_gauche(const Carre& carre) {
	if(carre.point.x + carre.longeur >  g_max or 
	   carre.point.y + carre.longeur > g_max) {
		return true;
	}
	return false;
}

bool test_validation_sup_gauche(const Carre& carre) {
	if(carre.point.x + carre.longeur > g_max or carre.point.y < 0) {
		   return true;
	   }
	   return false;
}

bool test_validation_sup_droite(const Carre& carre) {
	if(carre.point.x < 0 or carre.point.y < 0) {
		return true;
	}
	return false;
}

bool test_validation_inf_droite(const Carre& carre) {
	if(carre.point.x < 0 or carre.point.y + carre.longeur >= g_max) {
		return true;
	}
	return false;
} 

bool test_diago(const Carre& carre, const Carre& autre_carre) {
	if(carre.point.x % 2 == 0 and carre.point.y % 2 == 0 and 
	   autre_carre.point.x % 2 == 0 and autre_carre.point.y % 2 == 0) {
		   return true;
	 } else if(carre.point.x % 2 == 1 and carre.point.y % 2 == 0 and 
	          autre_carre.point.x % 2 == 1 and autre_carre.point.y % 2 == 0) {
				  return true;
	 } else if(carre.point.x % 2 == 0 and carre.point.y % 2 == 1 and 
	          autre_carre.point.x % 2 == 0 and autre_carre.point.y % 2 == 1) {
				  return true;
	} else if(carre.point.x % 2 == 1 and carre.point.y % 2 == 1 and 
	          autre_carre.point.x % 2 == 1 and autre_carre.point.y % 2 == 1) {
				  return true;
    } else if(carre.point.x % 2 == 0 and carre.point.y % 2 == 0 and 
			  autre_carre.point.x % 2 == 1 and autre_carre.point.y % 2 == 1) {
				  return true;
	} else if(carre.point.x % 2 == 1 and carre.point.y % 2 == 1 and 
			  autre_carre.point.x % 2 == 0 and autre_carre.point.y % 2 == 0) {
				  return true;
	} else if(carre.point.x % 2 == 0 and carre.point.y % 2 == 1 and 
			  autre_carre.point.x % 2 == 1 and autre_carre.point.y % 2 == 0) {
				  return true;
	}else if(carre.point.x % 2 == 1 and carre.point.y % 2 == 0 and 
			 autre_carre.point.x % 2 == 0 and autre_carre.point.y % 2 == 1) {
				  return true;
	}
	return false;
}

unsigned int test_chemin(Carre test, int saut1, int saut2) {
	Grid grid1 = grid;
	Carre autre_carre = test;
	unsigned int sup1(0);
	unsigned int sup2(0);
	bool bordure(false);
	if(saut1 > 0 and saut2 > 0) {
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_top_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y -=1;
			} else {
				test.point.x +=1;
				test.point.y +=1;
			}
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_top_bordure(test)) {
				bordure=false;
				
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y +=1;
			} else {
				test.point.x +=1;
				test.point.y -=1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_bottom_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y +=1;
			} else {
				test.point.x +=1;
				test.point.y -=1;
			}
			test_sup_chemin(test, sup2);
		}
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_bottom_bordure(test)) {
				bordure=false;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y -=1;
			
			} else {
				test.point.x +=1;
				test.point.y +=1;
			}
			test_sup_chemin(test, sup2);
		} 
		test = autre_carre;
	} else if(saut1 < 0 and saut2 < 0) {
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_top_bordure(test)) {
				
				bordure = true;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y -= 1;
			} else {
				test.point.x -=1;
				test.point.y += 1;
			}	
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_top_bordure(test)) {
				bordure= false;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y += 1;
			} else {
				test.point.x -=1;
				test.point.y -= 1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_bottom_bordure(test)) {
				bordure = true;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y += 1;
			} else {
				test.point.x -=1;
				test.point.y -= 1;
			}	
			test_sup_chemin(test, sup2);
		}
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_bottom_bordure(test)) {
				bordure = false;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y -= 1;
			} else {
				test.point.x -=1;
				test.point.y += 1;
			}	
			test_sup_chemin(test, sup2);
		} 
		test = autre_carre;
	} else if(saut1 < 0 and saut2 > 0) {
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_right_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y -= 1;
			} else {
				test.point.x +=1;
				test.point.y -= 1;
			}
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_right_bordure(test)) {
				bordure=false;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y -= 1;
			} else {
				test.point.x -=1;
				test.point.y -= 1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_left_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y -= 1;
			} else {
				test.point.x -=1;
				test.point.y -= 1;
			}
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_left_bordure(test)) {
				bordure=false;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y -= 1;
			} else {
				test.point.x +=1;
				test.point.y -= 1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
	} else if(saut1 > 0 and saut2 < 0 ) {
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_right_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y += 1;
			} else {
				test.point.x +=1;
				test.point.y += 1;
			}
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_right_bordure(test)) {
				bordure=false;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y += 1;
			} else {
				test.point.x -=1;
				test.point.y += 1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
		for(size_t i(0); i < abs(saut2); ++i) {
			if(test_deplacement_left_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x +=1;
				test.point.y += 1;
			} else {
				test.point.x -=1;
				test.point.y += 1;
			}
			test_sup_chemin(test, sup1);
		}
		for(size_t i(0); i < abs(saut1); ++i) {
			if(test_deplacement_left_bordure(test)) {
				bordure=true;
			}
			if(bordure==true) {
				test.point.x -=1;
				test.point.y += 1;
			} else {
				test.point.x +=1;
				test.point.y += 1;
			}
			test_sup_chemin(test, sup1);
		}
		test = autre_carre;
	}
	grid = grid1;
	if(sup2 < sup1) {
		return 2;
	}
	return 1;
}

void test_sup_chemin(const Carre& carre, unsigned int& sup) {
	for(size_t i(carre.point.y-carre.longeur/2);
	    i < carre.point.y + (carre.longeur/2+1); ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); 
		    j < carre.point.x + (carre.longeur/2+1); ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				grid[grid.size()-1-i][j] = false;
				++sup;
			}
		}
	}
}

bool test_deplacement_bordure(const Carre& carre, int& i) {
	if(carre.point.x-carre.longeur/2 == 0) {
		i=1;
		return true;
	}
	if(carre.point.x+carre.longeur/2 == g_max-1) {
		i=2;
		return true;
	}
	if(carre.point.y-carre.longeur/2 == 0) {
		i=3;
		return true;
	}
	if(carre.point.y+carre.longeur/2 == g_max-1) {
		i=4;
		return true;
	}
	return false;
}

bool test_deplacement_top_bordure(const Carre& carre) {
	if(carre.point.y+carre.longeur/2 == g_max-1) {
		return true;
	}
	return false;
}

bool test_deplacement_bottom_bordure(const Carre& carre) {
	if(carre.point.y+carre.longeur/2 == 0) {
		return true;
	}
	return false;
}

bool test_deplacement_left_bordure(const Carre& carre) {
	if(carre.point.x+carre.longeur/2 == 0) {
		return true;
	}
	return false;
}

bool test_deplacement_right_bordure(const Carre& carre) {
	if(carre.point.x+carre.longeur/2 == g_max-1) {
		return true;
	}
	return false;
}

	

bool find_place_in_carre(const Carre& carre1, Carre& carre2) {
	for(size_t i(carre1.point.y+1); i < carre1.point.y + carre1.longeur-carre2.longeur; ++i) {
		for(size_t j(carre1.point.x+1); j < carre1.point.x + carre1.longeur-carre2.longeur; ++j) {
			carre2.point.x = j+carre2.longeur/2;
			carre2.point.y = i+carre2.longeur/2;
			if(!test_superposition_sans_coord(carre2)) {
				return true;
			}
		}
	}
	return false;
}
	


void draw_carre(const Carre& carre, unsigned int style,
unsigned int couleur) {
	if(style==VIDE) {
		graphic_draw_carre_vide(carre.point.x, carre.point.y, carre.longeur, couleur);
	}
	if(style==LOSANGE) {
		graphic_draw_carre_losange(carre.point.x, carre.point.y, carre.longeur, couleur);
	}
	if(style==UNIFORME) {
		graphic_draw_carre_uniforme(carre.point.x-carre.longeur/2,
			carre.point.y-carre.longeur/2, carre.longeur, couleur);
	}
	if(style==DIAGONALE) {
		graphic_draw_carre_diagonale(carre.point.x-carre.longeur/2,
			carre.point.y-carre.longeur/2, carre.longeur, couleur);
	}
	if(style==GRILLE) {
		graphic_draw_carre_grille(carre.point.x-carre.longeur/2,
			carre.point.y-carre.longeur/2, carre.longeur, couleur);
	}
}
void affiche() {
	for(auto c : grid) {
		for(auto d : c) {
			cout << d ;
		}
		cout << endl;
	}
	cout << endl;
}



