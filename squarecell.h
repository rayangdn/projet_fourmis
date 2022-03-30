#ifndef SQUARECELL_H_INCLUDED
#define SQUARECELL_H_INCLUDED

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "constantes.h"
#include "message.h"
#include "error_squarecell.h"

using namespace std;

constexpr short unsigned g_dim(7);
//constexpr short unsigned g_max(pow(2, g_dim));
typedef vector<vector<bool>> Grid;

struct Point {
	unsigned int x;
	unsigned int y;
};
struct Carre {
	unsigned int longeur;
	Point point;
};

void initialise_grid(Grid&, const unsigned int);

void test_validation_carre(const Grid&, const Carre&);

void initialise_carre_non_centre(Grid&,const Carre&);

void initialise_carre_centre(Grid& grid,const Carre& carre);

void supprimer_carre_non_centre(Grid&, const Carre&);

void supprimer_carre_centre(Grid&, const Carre&);

bool test_superposition_2_carres(const Carre& ,const Carre&);

bool test_superposition(const Grid&, const Carre&);

#endif

