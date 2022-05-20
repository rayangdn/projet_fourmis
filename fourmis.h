#ifndef FOURMI_H_INCLUDED
#define FOURMI_H_INCLUDED

#include <fstream>

#include "constantes.h"
#include "food.h"
#include "squarecell.h"
#include "message.h"

class Fourmi{
public :
	Fourmi(Carre, unsigned int);
	virtual ~Fourmi() {};
	unsigned int get_age() const;
	Carre get_carre() const;
	bool get_end_of_life() const;
	virtual double get_total_food() const { return -1; }
	virtual void set_total_food(double total_food) {}
	virtual bool get_end_of_klan() const { return false; } 
	virtual bool test_chaque_fourmi(unsigned int, const Carre&)=0;
	bool fourmis_in_house(const Carre&);
	virtual void ecriture_frmi(std::ofstream&) const;
	virtual void draw_fourmis(unsigned int couleur)=0;
	virtual void consommation(unsigned int) { return; }
	virtual void deplacement_fourmi(const Carre&, Carre& carre_fourmi,
									Ensemble_food&, double& null) { return; }
	void incrementer_age();
	void deplacement_droite_haut();
	void deplacement_droite_bas();
	void deplacement_gauche_haut();
	void deplacement_gauche_bas();
	void deplacement_bas();
	void deplacement_gauche();
	void deplacement_droite();
	void deplacement_haut();
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&,
	unsigned int&)=0;
protected :
	void initialise_fourmi();
	Carre carre;
	unsigned int age;
	bool end_of_life;
};

typedef std::vector<std::unique_ptr<Fourmi>> Ensemble_fourmis;

class Generator : public Fourmi{
public :
	Generator(Carre, unsigned int);
	~Generator() {};
	virtual double get_total_food() const override;
	virtual void set_total_food(double total_food) override;
	virtual bool get_end_of_klan() const override;
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
	virtual void draw_fourmis(unsigned int) override;
	virtual void consommation(unsigned int) override;
	virtual void deplacement_fourmi(const Carre& carre_f, Carre& carre_fourmi,
									Ensemble_food&, double& null) override;
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
	unsigned int&) override;
private :
	bool superposition_fourmi_G();
	bool fourmis_in_house_G(unsigned int, const Carre&);
	bool generator_good_position(const Carre&);
	double total_food;
	bool end_of_klan;
};

class Collector : public Fourmi {
public :
	Collector(Carre, unsigned int);
	~Collector () {};
	void initialise_collect(const Carre&, unsigned int, std::string);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
	virtual void draw_fourmis(unsigned int) override;
	virtual void deplacement_fourmi(const Carre&, Carre& carre_fourmi,
									Ensemble_food&, double& total_food) override;
	void deplacement_collector_loaded(const Carre& carre_f, Carre carre_generator, 
									  double& total_food);
	void deplacement_collector_empty(const Carre& carre_f, Ensemble_food&);
	int test_diago_proximities(const Ensemble_food&);
	void deplacement_collector_out(const Carre&);
	bool deplacement_chemin_1_empty(const Carre&, int, int);
	bool deplacement_chemin_2_empty(const Carre&, int , int);
	bool deplacement_chemin_1_loaded(const Carre& carre_f,  int vx, int vy);
	bool deplacement_chemin_2_loaded(const Carre&, Carre carre_generator, int, int);
	void test_saut_bordure(int i, int& saut_bordure, int vx, int vy, int saut1, int saut2);
	unsigned int best_chemin(int& saut1, int& saut2, int vx, int vy);
	void deplacement_no_bordure(int chemin , int saut1, int saut2);
	void deplacement_bordure(int i, int saut1, int saut_bordure, bool& bordure);
	void deplacement_left_bordure(int& j, int saut1, int saut_bordure, bool& bordure);
	void deplacement_right_bordure(int& j, int saut1, int saut_bordure, bool& bordure);
	void deplacement_bottom_bordure(int& j, int saut1, int saut_bordure, bool& bordure);
	void deplacement_top_bordure(int& j, int saut1, int saut_bordure, bool& bordure);
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
	unsigned int&) override;
private :
	bool superposition_fourmi_C();
	Etat_collector etat_c;
};

class Defensor : public Fourmi{
public :
	Defensor(Carre, unsigned int);
	~Defensor() {};
	void initialise_defens(const Carre&, unsigned int);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(unsigned int) override;
	virtual void deplacement_fourmi(const Carre&, Carre& carre_fourmi,
									Ensemble_food&, double& null) override;
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
									unsigned int&) override;
private :
	bool superposition_fourmi_D();
	bool fourmis_in_house_D(unsigned int, const Carre&);
};

class Predator: public Fourmi {
public :
	Predator(Carre, unsigned int);
	~Predator() {};
	void initialise_predat(const Carre&, unsigned int);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(unsigned int) override;
	//virtual void deplacement_fourmi(const Carre&, Ensemble_food&, Fourmi*) override;
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
	unsigned int&) override;
private :
	bool superposition_fourmi_P();
};

void decodage_line_fourmis(std::string, unsigned int, Collector&, Defensor&,
Predator&);

#endif
