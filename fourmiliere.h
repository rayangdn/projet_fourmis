#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

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
	bool test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
	unsigned int);
	void ajouter_fourmis(Fourmi*);
	bool test_fourmis(unsigned int, unsigned int);
	void supprimer_fourmis();
	void draw_fourmiliere(unsigned int);
	void ecriture_fourmiliere(std::ofstream&) const;
private :
	Carre carre; 
	unsigned int nbC, nbD, nbP;
	Ensemble_fourmis ensemble_fourmis;
};

typedef std::vector<Fourmiliere> Ensemble_fourmilieres;

bool decodage_line_fourmiliere(std::string, Ensemble_fourmilieres&, unsigned int, int&);

bool decodage_line_ensemble_fourmis(std::string, Fourmiliere *,
unsigned int& , unsigned int& , unsigned int&, unsigned int&, unsigned int&,
unsigned int&, unsigned int&, unsigned int&, unsigned int&);

#endif
