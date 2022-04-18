//fourmi.cc
//Rayan Gauderon membre1: 60%
//Maxime Luyet membre 2: 40%

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "fourmis.h"

using namespace std;

Fourmi::Fourmi(Carre carre) : carre(carre) {}

Generator::Generator(Carre carre, unsigned int total_food) 
: Fourmi(carre), total_food(total_food) {}

Collector::Collector(Carre carre, unsigned int age, bool have_food)
: Fourmi(carre), age(age), have_food(have_food) {}

Defensor::Defensor(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

Predator::Predator(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

void Fourmi::initialise_fourmi() {
	initialise_carre_centre(carre);
}

bool Fourmi::fourmis_in_house(const Carre& carre_fourmiliere) { 
	if(((carre.point.x-carre.longeur/2) <= (carre_fourmiliere.point.x)) or
		((carre.point.y-carre.longeur/2) <= (carre_fourmiliere.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= 
		(carre_fourmiliere.point.x + carre_fourmiliere.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= 
		(carre_fourmiliere.point.y +carre_fourmiliere.longeur))) {
			return true;
		}
	return false;
}

void Generator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere,
bool& erreur) {
	test_validation_carre_centre(carre, erreur);
	if(erreur==false) {
		superposition_fourmi_G(erreur);
	}
	if(erreur==false) {
		fourmis_in_house_G(countF, carre_fourmiliere, erreur);
	}
	initialise_fourmi();
}

void Generator::superposition_fourmi_G(bool& erreur) {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::generator_overlap( carre.point.x, carre.point.y,x,y);
		erreur = true;
	}
}

void Generator::fourmis_in_house_G(unsigned int countF, const Carre& carre_fourmiliere,
bool& erreur) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::generator_not_within_home(carre.point.x, carre.point.y,
		countF);
		erreur = true;
	}
}

void Generator::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_gene_predat(carre, graphic, couleur);
}

void Collector::initialise_collect(const Carre& autre_carre, unsigned int autre_age,
string autre_have_food) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
	if(autre_have_food == "true") {
		have_food=true;
	} else { 
		have_food=false;
	}
}

void Collector::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere,
bool& erreur) {
	test_validation_carre_centre(carre, erreur);
	if(erreur==false) {
		superposition_fourmi_C(erreur);
	}
	initialise_fourmi();

}
void Collector::superposition_fourmi_C(bool& erreur) {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::collector_overlap( carre.point.x, carre.point.y, x, y);
		erreur = true;
	}
}

void Collector::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_collector(carre, graphic, couleur);
	if(have_food) {
		Carre carre_food{1, {carre.point.x, 
		carre.point.y}};
		draw_carre_food(carre_food, graphic);
	}
}

void Defensor::initialise_defens(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

void Defensor::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere, 
bool& erreur) {
	test_validation_carre_centre(carre, erreur);
	if(erreur==false) {
		superposition_fourmi_D(erreur);
	}
	if(erreur==false) {
		fourmis_in_house_D(countF, carre_fourmiliere, erreur);
	}
	initialise_fourmi();
}


void Defensor::superposition_fourmi_D(bool& erreur) {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::defensor_overlap( carre.point.x, carre.point.y, x, y );
		erreur = true;
	}
}

void Defensor::fourmis_in_house_D(unsigned int countF, const Carre& carre_fourmiliere,
bool& erreur) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::defensor_not_within_home(carre.point.x, carre.point.y,
		countF);
		erreur = true;
	}
}

void Defensor::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_defensor(carre, graphic, couleur);
}

void Predator::initialise_predat(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

void Predator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere, 
bool& erreur) {
	test_validation_carre_centre(carre, erreur);
	if(erreur==false) {
		superposition_fourmi_P(erreur);
	}
	initialise_fourmi();
}

void Predator::superposition_fourmi_P(bool& erreur) {
	if(test_superposition_sans_coord(carre)) {
		cout << message::predator_overlap(carre.point.x, carre.point.y);
		erreur = true;
	}
}

void Predator::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_gene_predat(carre, graphic, couleur);
}

void decodage_line_fourmis(string line, unsigned int etat, Collector& collector,
Defensor& defensor, Predator& predator, bool& erreur) {
	istringstream data(line);
	unsigned int x, y, age;
	string have_food;
	if(etat==1) {
		data >> x >> y >> age >> have_food;
		Carre carre{sizeC, {x, y}};
		collector.initialise_collect(carre, age, have_food);
		return;
	}
	
	if(etat==2) {
		data >> x >> y >> age;
		Carre carre{sizeD, {x, y}};
		defensor.initialise_defens(carre, age);
		return;
	}
	if(etat==3) {
		data >> x >> y >> age;
		Carre carre{sizeP, {x, y}};
		predator.initialise_predat(carre, age);
		return;
	}
}
