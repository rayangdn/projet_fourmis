#ifndef FOURMI_H_INCLUDED
#define FOURMI_H_INCLUDED

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "food.h"
#include "squarecell.h"
#include "message.h"

class Fourmi{
	public :
	Fourmi(Carre);
	virtual ~Fourmi() {};
	/*virtual void test_superposition_fourmi(const Grid&) = 0;
	virtual void fourmis_in_house(int, const Carre&) = 0;*/
	virtual void test_chaque_fourmi(Grid&, unsigned int, const Carre&)=0;
	void initialise_fourmi(Grid&);
	protected :
	Carre carre;
};
typedef vector<unique_ptr<Fourmi>> Ensemble_fourmis;



class Generator : public Fourmi{
	public :
	Generator(Carre, unsigned int);
	~Generator() {};
	unsigned int getlongeur() { return carre.longeur ; }
	virtual void test_chaque_fourmi(Grid&, unsigned int, const Carre&) override;
	void superposition_fourmi_G(Grid&);
	void fourmis_in_house_G(unsigned int,const Carre&);
	private :
	unsigned int total_food;
	
};
class Collector : public Fourmi{
	public :
	Collector(Carre,unsigned int, string);
	~Collector () {};
	void initialise_collect(const Carre&, unsigned int, string);
	virtual void test_chaque_fourmi(Grid&, unsigned int, const Carre&) override;
	void superposition_fourmi_C(Grid&);
	private :
	unsigned int age;
	string have_food;
	
};
class Defensor : public Fourmi{
	public :
	Defensor(Carre, unsigned int);
	~Defensor() {};
	void initialise_defens(const Carre&, unsigned int);
	virtual void test_chaque_fourmi(Grid&, unsigned int, const Carre&) override;
	void superposition_fourmi_D(Grid&);
	void fourmis_in_house_D(unsigned int,const Carre&);
	private :
	unsigned int age;
	
};
class Predator: public Fourmi {
	public :
	Predator(Carre, unsigned int);
	~Predator() {};
	void initialise_predat(const Carre&, unsigned int);
	virtual void test_chaque_fourmi(Grid&, unsigned int, const Carre&) override;
	void superposition_fourmi_P(Grid&);
	
	
	private :
	unsigned int age;
	
};
void decodage_line_fourmis(std::string, Grid&, unsigned int, Collector&, Defensor&, Predator&);

#endif
