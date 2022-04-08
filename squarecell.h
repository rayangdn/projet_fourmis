#ifndef SQUARECELL_H_INCLUDED
#define SQUARECELL_H_INCLUDED


#include <cmath>

#include "constantes.h"
#include "message.h"
#include "error_squarecell.h"
#include "graphic.h"

constexpr short unsigned g_dim(7);
const short unsigned g_max(pow(2, g_dim));

typedef std::vector<std::vector<bool>> Grid;
static Grid grid;


struct Point {
	unsigned int x;
	unsigned int y;
};
struct Carre {
	unsigned int longeur;
	Point point;
};

void initialise_grid(const unsigned int&);

void test_validation_carre_non_centre(const Carre&);

void test_validation_carre_centre(const Carre&);

void initialise_carre_non_centre(const Carre&);

void initialise_carre_centre(const Carre&);

void supprimer_carre_non_centre(const Carre&);

void supprimer_carre_centre(const Carre&);

bool test_superposition_2_carres(const Carre&, const Carre&);

bool test_superposition_avec_coord(const Carre&, unsigned int&, unsigned int&);

bool test_superposition_sans_coord(const Carre&);

#endif

