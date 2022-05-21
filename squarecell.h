#ifndef SQUARECELL_H_INCLUDED
#define SQUARECELL_H_INCLUDED


#include "error_squarecell.h"
#include "graphic.h"

typedef std::vector<std::vector<bool>> Grid;

static Grid grid;

struct Point {
	int x;
	int y;
};
struct Carre {
	unsigned int longeur;
	Point point;
};

void supprimer_grid();

void initialise_grid(const unsigned int&);

bool test_validation_carre_non_centre(const Carre&);

bool test_validation_carre_centre(const Carre&);

bool test_validation_carre_centre_no_mess(const Carre&);

bool test_validation_carre_no_bound(const Carre&);

void initialise_carre_non_centre(const Carre&);

void initialise_carre_centre(const Carre&);

void supprimer_carre_non_centre(const Carre&);

void supprimer_carre_centre(const Carre&);

bool test_superposition_2_carres_non_centre(const Carre&, const Carre&);

bool test_superposition_2_carres_centre(const Carre&, const Carre&);

bool test_superposition_2_carres_non_centre_centre(const Carre&, const Carre&);

bool test_superposition_avec_coord(const Carre&, unsigned int&, unsigned int&);

bool test_superposition_sans_coord(const Carre&);

bool test_validation_inf_gauche(const Carre&);

bool test_validation_sup_gauche(const Carre&);

bool test_validation_sup_droite(const Carre&);

bool test_validation_inf_droite(const Carre&);

bool test_diago(const Carre&, const Carre&);

unsigned int test_chemin(Carre, int, int, bool&);

bool test_deplacement_bordure(const Carre& carre, int& i);

void test_deplacement_1(const Carre& autre_carre, Carre test, int saut1, int saut2, 
						unsigned int& sup1, unsigned int& sup2, bool& bordure);
						
void test_deplacement_2(const Carre& autre_carre, Carre test, int saut1, int saut2, 
						unsigned int& sup1, unsigned int& sup2, bool& bordure);

void test_deplacement_3(const Carre& autre_carre, Carre test, int saut1, int saut2, 
						unsigned int& sup1, unsigned int& sup2, bool& bordure);

void test_deplacement_4(const Carre& autre_carre, Carre test, int saut1, int saut2, 
						unsigned int& sup1, unsigned int& sup2, bool& bordure);

bool test_deplacement_top_bordure(const Carre& carre);

bool test_deplacement_bottom_bordure(const Carre& carre);

bool test_deplacement_left_bordure(const Carre& carre);

bool test_deplacement_right_bordure(const Carre& carre);

void test_sup_chemin(const Carre& carre, unsigned int& sup);

bool find_place_in_carre(const Carre&, Carre&);

void draw_carre(const Carre&, unsigned int, unsigned int);

void affiche();

#endif

