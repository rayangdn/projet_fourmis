#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

#include "fourmis.h"
#include "squarecell.h"
#include "food.h"
#include "message.h"



class Fourmiliere {
public :
	Fourmiliere(Carre ,unsigned int, unsigned int ,unsigned int);
	void test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
	unsigned int, bool&);
	void ajouter_fourmis(Fourmi*);
	void test_fourmis(unsigned int, unsigned int, bool&);
	void supprimer_fourmis();
	void draw_fourmiliere(Graphic, Couleur couleur);
	
private :
	Carre carre; 
	unsigned int nbC, nbD, nbP;
	Ensemble_fourmis ensemble_fourmis;
};

typedef std::vector<Fourmiliere> Ensemble_fourmilieres;

void decodage_line_fourmiliere(std::string, Ensemble_fourmilieres&, bool&);

#endif
