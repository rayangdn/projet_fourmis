#ifndef FOURMI_H_INCLUDED
#define FOURMI_H_INCLUDED



#include "food.h"
#include "squarecell.h"
#include "message.h"
//#include "fourmiliere.h"

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
	void test_chaque_fourmi(Grid&, unsigned int, const Carre&);
	void superposition_fourmi_G(Grid&);
	void fourmis_in_house_G(int,const Carre&);
	private :
	unsigned int total_food;
	
};
class Collector : public Fourmi{
	public :
	Collector(Carre,unsigned int, string);
	~Collector () {};
	void test_chaque_fourmi(Grid&, unsigned int, const Carre&);
	void superposition_fourmi_C(Grid&);
	private :
	unsigned int age;
	string have_food;
	
};
class Defensor : public Fourmi{
	public :
	Defensor(Carre, unsigned int);
	~Defensor() {};
	void test_chaque_fourmi(Grid&, unsigned int, const Carre&);
	void superposition_fourmi_D(Grid&);
	void fourmis_in_house_D(int,const Carre&);
	private :
	unsigned int age;
	
};
class Predator: public Fourmi {
	public :
	Predator(Carre, unsigned int);
	~Predator() {};
	void test_chaque_fourmi(Grid&, unsigned int, const Carre&);
	void superposition_fourmi_P(Grid&);
	
	private :
	unsigned int age;
	
};
unsigned int decodage_line_fourmis(std::string, Grid&, unsigned int, unsigned int, unsigned int);

#endif
