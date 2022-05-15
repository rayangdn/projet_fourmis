#ifndef FOURMILIERE_H_INCLUDED
#define FOURMILIERE_H_INCLUDED

#include "fourmis.h"
#include "squarecell.h"
#include "food.h"
#include "message.h"

class Fourmiliere {
public :
	Fourmiliere(Carre ,unsigned int, unsigned int ,unsigned int, unsigned int,
	unsigned int, unsigned int);
	double get_total_food() const;
	unsigned int get_nbC() const;
	unsigned int get_nbD() const;
	unsigned int get_nbP() const;
	Carre get_carre() const;
	bool test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
										unsigned int);
	
	//void test_inf_gauche(const Carre&, unsigned int&);
	//void test_sup_gauche(const Carre&, unsigned int&);
	void ajouter_fourmis(Fourmi*);
	bool test_fourmis(unsigned int, unsigned int);
	void ecriture_fourmiliere(std::ofstream&) const;
	void draw_fourmiliere();
	void calcul_sizeF();
	bool test_expend(const Fourmiliere&, unsigned int& k);
	bool superposition_inf_gauche(const Carre&, unsigned int, unsigned int&);
	bool superposition_sup_gauche(const Carre&, unsigned int, unsigned int&);
	void expend(unsigned int);
	void maj_generator();
	void create_fourmi();
	void deplacement_generator(Ensemble_food& ensemble_foo);
	bool recherche_espace_libre(Carre&);
	void action_autres_fourmis(Ensemble_food& ensemble_foo);
	void destruction_fourmis(Ensemble_food&);
	bool destruction_fourmiliere();
private :
	Carre carre;
	unsigned int nbC, nbD, nbP, nbT;
	unsigned int sizeF;
	unsigned int color;
	Ensemble_fourmis ensemble_fourmis;
	Etat_fourmiliere etat_f;
	bool test_inf_gauche();
	bool test_sup_gauche();
	bool test_sup_droite();
	bool test_inf_droite();
	
};

typedef std::vector<Fourmiliere> Ensemble_fourmilieres;

bool decodage_line_fourmiliere(std::string, Ensemble_fourmilieres&, unsigned int, int&);

bool decodage_line_ensemble_fourmis(std::string, Fourmiliere *,
									unsigned int& , unsigned int& , unsigned int&, 
									unsigned int&, unsigned int&, unsigned int&, 
									unsigned int&, unsigned int&, unsigned int&,
									unsigned int&);
#endif
