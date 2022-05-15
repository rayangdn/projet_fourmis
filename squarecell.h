#ifndef SQUARECELL_H_INCLUDED
#define SQUARECELL_H_INCLUDED

#include "message.h"
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

bool test_superposition_2_carres(const Carre&, const Carre&);

bool test_superposition_2_carres_centre(const Carre&, const Carre&);

bool test_superposition_2_carres_non_centre_centre(const Carre&, const Carre&);

bool test_superposition_avec_coord(const Carre&, unsigned int&, unsigned int&);

bool test_superposition_sans_coord(const Carre&);

bool test_validation_inf_gauche(const Carre&);

bool test_validation_sup_gauche(const Carre&);

bool test_validation_sup_droite(const Carre&);

bool test_validation_inf_droite(const Carre&);

//bool test_superposition_inf_gauche(const Carre&, const Carre&);

//bool test_superposition_sup_gauche(const Carre&, const Carre&);

bool test_diago(const Carre&, const Carre&);

bool find_place_in_carre(const Carre&, Carre&);

void draw_carre(const Carre&, unsigned int, unsigned int);



#endif

