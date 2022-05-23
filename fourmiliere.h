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
	unsigned int get_etat_f() const;
	double get_total_food() const;
	unsigned int get_nbC() const;
	unsigned int get_nbD() const;
	unsigned int get_nbP() const;
	unsigned int get_sizeF() const;
	Carre get_carre() const;
	bool test_superposition_fourmiliere(const Fourmiliere&, unsigned int,
										unsigned int);
	void ajouter_fourmis(Fourmi*);
	void ajouter_fourmis(Fourmi*, unsigned int);
	bool test_fourmis(unsigned int, unsigned int);
	void ecriture_fourmiliere(std::ofstream&) const;
	void draw_fourmiliere();
	void calcul_sizeF();
	bool test_inf_gauche(Fourmiliere&);
	bool test_sup_gauche(Fourmiliere&);
	bool test_sup_droite(Fourmiliere&);
	bool test_inf_droite(Fourmiliere&);
	void mise_a_jour(int);
	void maj_generator(Ensemble_food&);
	void create_fourmi();
	void create_fourmi_free();
	void create_fourmi_constrained();
	bool recherche_espace_libre(Carre&);
	void fourmi_kill(Fourmiliere&, unsigned int);
	void intrusion_fourmi(Fourmiliere&, std::vector<Carre>&);
	void closest_fourmi(Fourmiliere&, std::vector<Carre>&);
	void predator_in_house();
	void deplacement_predator(std::vector<Carre>);
	void action_autres_fourmis(Ensemble_food&);
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
