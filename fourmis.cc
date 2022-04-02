#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "fourmis.h"

//membre1: 60%
//membre 2: 40%

using namespace std;

Fourmi::Fourmi(Carre carre) : carre(carre) {}

Generator::Generator(Carre carre, unsigned int total_food) 
: Fourmi(carre), total_food(total_food) {}

Collector::Collector(Carre carre, unsigned int age, string have_food)
: Fourmi(carre), age(age), have_food(have_food) {}

Defensor::Defensor(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

Predator::Predator(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

void Fourmi::initialise_fourmi() {
	initialise_carre_centre(carre);
}

bool Fourmi::fourmis_in_house(const Carre& autre_carre) { //autre_carre = carre fourmiliere
	if(((carre.point.x-carre.longeur/2) <= (autre_carre.point.x)) or
		((carre.point.y-carre.longeur/2) <= (autre_carre.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= 
		(autre_carre.point.x + autre_carre.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= 
		(autre_carre.point.y + autre_carre.longeur))) {
			return true;
		}
	return false;
}

void Generator::test_chaque_fourmi(unsigned int countF, const Carre& carre) {
	superposition_fourmi_G();
	fourmis_in_house_G(countF, carre);
	initialise_fourmi();
}

void Generator::superposition_fourmi_G() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::generator_overlap( carre.point.x, carre.point.y,x,y);
		exit(EXIT_FAILURE);
	}
}

void Generator::fourmis_in_house_G(unsigned int countF, const Carre& autre_carre) {
	if(fourmis_in_house(autre_carre)) {
		cout << message::generator_not_within_home(carre.point.x, carre.point.y,
		countF);
		exit(EXIT_FAILURE); 
	}
}

void Collector::initialise_collect(const Carre& autre_carre, unsigned int autre_age,
string autre_have_food) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
	have_food = autre_have_food;
}

void Collector::test_chaque_fourmi(unsigned int countF, const Carre& autre_carre) {
	superposition_fourmi_C();
	initialise_fourmi();
}

void Collector::superposition_fourmi_C() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::collector_overlap( carre.point.x, carre.point.y, x, y);
		exit(EXIT_FAILURE);
	}
}

void Defensor::initialise_defens(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

void Defensor::test_chaque_fourmi(unsigned int countF, const Carre& autre_carre) {
	fourmis_in_house_D(countF, autre_carre);
	superposition_fourmi_D();
	initialise_fourmi();
}

void Defensor::superposition_fourmi_D() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::defensor_overlap( carre.point.x, carre.point.y, x, y );
		exit(EXIT_FAILURE);
	}
}

void Defensor::fourmis_in_house_D(unsigned int countF, const Carre& autre_carre) {
	if(fourmis_in_house(autre_carre)) {
		cout << message::defensor_not_within_home(carre.point.x, carre.point.y,
		countF);
		exit(EXIT_FAILURE); 
	}
}

void Predator::initialise_predat(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

void Predator::test_chaque_fourmi(unsigned int countF, const Carre& autre_carre) {
	superposition_fourmi_P();
	initialise_fourmi();
}

void Predator::superposition_fourmi_P() {
	if(test_superposition_sans_coord(carre)) {
		cout << message::predator_overlap(carre.point.x, carre.point.y);
		exit(EXIT_FAILURE);
	}
}

void decodage_line_fourmis(string line, unsigned int etat, Collector& collector,
Defensor& defensor, Predator& predator) {
	istringstream data(line);
	unsigned int x, y, age;
	string have_food;
	if(etat==1) {
		data >> x >> y >> age >> have_food;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(carre);
		collector.initialise_collect(carre, age, have_food);
		return;
	}
	
	if(etat==2) {
		data >> x >> y >> age;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(carre);
		defensor.initialise_defens(carre, age);
		return;
	}
	if(etat==3) {
		data >> x >> y >> age;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(carre);
		predator.initialise_predat(carre, age);
		return;
	}
}
