#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

#include <fstream>

#include "fourmis.h"
#include "squarecell.h"
#include "food.h"
#include "message.h"



class Fourmiliere {
public :
	Fourmiliere(Carre ,unsigned int, unsigned int ,unsigned int);
	unsigned int get_total_food() const;
	unsigned int get_nbC() const;
	unsigned int get_nbD() const;
	unsigned int get_nbP() const;
	void test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
	unsigned int, bool&);
	void ajouter_fourmis(Fourmi*);
	void test_fourmis(unsigned int, unsigned int, bool&);
	void supprimer_fourmis();
	void draw_fourmiliere(Graphic, Couleur couleur);
	void ecriture_fourmiliere(std::ofstream&, unsigned int) const;

	
private :
	Carre carre; 
	unsigned int nbC, nbD, nbP;
	Ensemble_fourmis ensemble_fourmis;
};

typedef std::vector<Fourmiliere> Ensemble_fourmilieres;

bool decodage_line_fourmiliere(std::string, Ensemble_fourmilieres&, bool&, unsigned int);

#endif
