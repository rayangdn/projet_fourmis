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
	bool get_end_of_life() const;
	virtual double get_total_food() const { return -1; }
	virtual bool get_end_of_klan() const { return false; } 
	virtual bool test_chaque_fourmi(unsigned int, const Carre&)=0;
	virtual void ecriture_frmi(std::ofstream&) const;
	virtual void draw_fourmis(unsigned int couleur)=0;
	virtual void consommation(unsigned int) { return; }
	virtual void deplacement_fourmi(const Carre&) { return; }
	void incrementer_age();
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&,
	unsigned int&)=0;
protected :
	void initialise_fourmi();
	bool fourmis_in_house(const Carre&);
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
	virtual bool get_end_of_klan() const override;
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
	virtual void draw_fourmis(unsigned int) override;
	virtual void consommation(unsigned int) override;
	virtual void deplacement_fourmi(const Carre&) override;
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
	unsigned int&) override;
private :
	bool superposition_fourmi_G();
	bool fourmis_in_house_G(unsigned int, const Carre&);
	double total_food;
	bool end_of_klan;
};

class Collector : public Fourmi{
public :
	Collector(Carre, unsigned int);
	~Collector () {};
	void initialise_collect(const Carre&, unsigned int, std::string);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
	virtual void draw_fourmis(unsigned int) override;
//	virtual void deplacement_fourmi(const Carre&) override;
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
	virtual void deplacement_fourmi(const Carre&) override;
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
	//virtual void deplacement_fourmi(const Carre&) override;
	virtual void destruction_fourmi(Ensemble_food&, unsigned int&, unsigned int&, 
	unsigned int&) override;
private :
	bool superposition_fourmi_P();
};

void decodage_line_fourmis(std::string, unsigned int, Collector&, Defensor&,
Predator&);

#endif
