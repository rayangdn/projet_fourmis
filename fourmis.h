#ifndef FOURMI_H_INCLUDED
#define FOURMI_H_INCLUDED

#include <memory>

#include "food.h"
#include "squarecell.h"
#include "message.h"

class Fourmi{
public :
	Fourmi(Carre);
	virtual ~Fourmi() {};
	virtual void test_chaque_fourmi(unsigned int, const Carre&, bool&)=0;
	void initialise_fourmi();
	bool fourmis_in_house(const Carre&);
protected :
	Carre carre;
};

typedef std::vector<std::unique_ptr<Fourmi>> Ensemble_fourmis;

class Generator : public Fourmi{
public :
	Generator(Carre, unsigned int);
	~Generator() {};
	virtual void test_chaque_fourmi(unsigned int, const Carre&, bool&) override;
	void superposition_fourmi_G(bool&);
	void fourmis_in_house_G(unsigned int, const Carre&, bool&);
private :
	unsigned int total_food;
};

class Collector : public Fourmi{
public :
	Collector(Carre,unsigned int, std::string);
	~Collector () {};
	void initialise_collect(const Carre&, unsigned int, std::string);
	virtual void test_chaque_fourmi(unsigned int, const Carre&, bool&) override;
	void superposition_fourmi_C(bool&);
private :
	unsigned int age;
	std::string have_food;
};

class Defensor : public Fourmi{
public :
	Defensor(Carre, unsigned int);
	~Defensor() {};
	void initialise_defens(const Carre&, unsigned int);
	virtual void test_chaque_fourmi(unsigned int, const Carre&, bool&) override;
	void superposition_fourmi_D(bool&);
	void fourmis_in_house_D(unsigned int, const Carre&, bool&);
	private :
	unsigned int age;
};

class Predator: public Fourmi {
public :
	Predator(Carre, unsigned int);
	~Predator() {};
	void initialise_predat(const Carre&, unsigned int);
	virtual void test_chaque_fourmi(unsigned int, const Carre&, bool&) override;
	void superposition_fourmi_P(bool&);
private :
	unsigned int age;
};

void decodage_line_fourmis(std::string, unsigned int, Collector&, Defensor&,
Predator&, bool&);

#endif
