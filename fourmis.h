#ifndef FOURMI_H_INCLUDED
#define FOURMI_H_INCLUDED

#include <memory>
#include <fstream>
#include "constantes.h"
#include "food.h"
#include "squarecell.h"
#include "message.h"

class Fourmi{
public :
	Fourmi(Carre);
	virtual ~Fourmi() {};
	virtual unsigned int get_total_food() const= 0;
	virtual bool test_chaque_fourmi(unsigned int, const Carre&)=0;
	virtual void draw_fourmis(Graphic graphic, Couleur couleur)=0;
	virtual void ecriture_frmi(std::ofstream&) const =0;
protected :
	void initialise_fourmi();
	bool fourmis_in_house(const Carre&);
	Carre carre;
};

typedef std::vector<std::unique_ptr<Fourmi>> Ensemble_fourmis;

class Generator : public Fourmi{
public :
	Generator(Carre, unsigned int);
	~Generator() {};
	virtual unsigned int get_total_food() const override;
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(Graphic graphic, Couleur couleur) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
private :
	bool superposition_fourmi_G();
	bool fourmis_in_house_G(unsigned int, const Carre&);
	unsigned int total_food;
};

class Collector : public Fourmi{
public :
	Collector(Carre,unsigned int, bool);
	~Collector () {};
	virtual unsigned int get_total_food() const override { return 0;}
	void initialise_collect(const Carre&, unsigned int, std::string);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(Graphic graphic, Couleur couleur) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
private :
	bool superposition_fourmi_C();
	unsigned int age;
	bool have_food;
};

class Defensor : public Fourmi{
public :
	Defensor(Carre, unsigned int);
	~Defensor() {};
	virtual unsigned int get_total_food() const override { return 0;}
	void initialise_defens(const Carre&, unsigned int);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(Graphic graphic, Couleur couleur) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
private :
	bool superposition_fourmi_D();
	bool fourmis_in_house_D(unsigned int, const Carre&);
	unsigned int age;
};

class Predator: public Fourmi {
public :
	Predator(Carre, unsigned int);
	~Predator() {};
	virtual unsigned int get_total_food() const override { return 0;}
	void initialise_predat(const Carre&, unsigned int);
	virtual bool test_chaque_fourmi(unsigned int, const Carre&) override;
	virtual void draw_fourmis(Graphic graphic, Couleur couleur) override;
	virtual void ecriture_frmi(std::ofstream&) const override;
private :
	bool superposition_fourmi_P();
	unsigned int age;
};

void decodage_line_fourmis(std::string, unsigned int, Collector&, Defensor&,
Predator&);

#endif
