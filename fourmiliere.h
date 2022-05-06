#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

#include "fourmis.h"
#include "squarecell.h"
#include "food.h"
#include "message.h"

class Fourmiliere {
public :
	Fourmiliere(Carre ,unsigned int, unsigned int ,unsigned int, unsigned int,
	unsigned int sizeF);
	double get_total_food() const;
	unsigned int get_nbC() const;
	unsigned int get_nbD() const;
	unsigned int get_nbP() const;
	Carre get_Carre() const;
	bool test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
										unsigned int);
	bool test_fourmiliere_no_mess(const Fourmiliere&);
	void ajouter_fourmis(Fourmi*);
	bool test_fourmis(unsigned int, unsigned int);
	void ecriture_fourmiliere(std::ofstream&) const;
	void draw_fourmiliere(unsigned int);
	void calcul_sizeF();
	void expend_restrict();
	void maj_generator();
	void create_fourmi();
	void deplacement_generator();
	void recherche_espace_libre(Carre&);
	void action_autres_fourmis();
	void destruction_fourmis(Ensemble_food&);
	bool destruction_fourmiliere();
private :
	Carre carre;
	unsigned int nbC, nbD, nbP, nbT;
	unsigned int sizeF;
	Ensemble_fourmis ensemble_fourmis;
	Etat_fourmiliere etat_f;
};

typedef std::vector<Fourmiliere> Ensemble_fourmilieres;

bool decodage_line_fourmiliere(std::string, Ensemble_fourmilieres&, unsigned int, int&);

bool decodage_line_ensemble_fourmis(std::string, Fourmiliere *,
									unsigned int& , unsigned int& , unsigned int&, 
									unsigned int&, unsigned int&, unsigned int&, 
									unsigned int&, unsigned int&, unsigned int&);

void reinitialise();

#endif
