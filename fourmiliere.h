#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "fourmis.h"
#include "squarecell.h"
#include "food.h"
#include "message.h"



class Fourmiliere {
	public :
	Fourmiliere(Carre ,unsigned int, unsigned int ,unsigned int);
	//~Fourmiliere() {};
	void test_superposition_fourmiliere(const Fourmiliere&, unsigned int, unsigned int);
	
	void ajouter_fourmis(Fourmi*);
	void test_fourmis(Grid&, unsigned int, unsigned int);
	
	private :
	Carre carre; 
	unsigned int nbC, nbD, nbP;
	Ensemble_fourmis ensemble_fourmis;
	
};
typedef vector<Fourmiliere> Ensemble_fourmiliere;

void decodage_line_fourmiliere(std::string, Grid&, unsigned int, Ensemble_fourmiliere&);

#endif
