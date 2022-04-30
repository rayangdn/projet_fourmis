//fourmi.cc
//Rayan Gauderon membre1: 60%
//Maxime Luyet membre 2: 40%

#include <cstdlib>
#include <string>
#include <iostream>
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

unsigned int Generator::get_total_food() const {
	return total_food;
}

bool Generator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_G()) {
		return true;
	}
	if(fourmis_in_house_G(countF, carre_fourmiliere)) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Generator::superposition_fourmi_G() {
	unsigned int x, y;
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::generator_overlap(carre.point.x, carre.point.y, x, y);
		return true;
	}
	return false;
}

bool Generator::fourmis_in_house_G(unsigned int countF, const Carre& carre_fourmiliere) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::generator_not_within_home(carre.point.x, carre.point.y,
		countF);
		return true;
	}
	return false;
}

void Generator::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_uniforme(carre, graphic, couleur);
}

void Generator::ecriture_frmi(ofstream& fichier) const {
	fichier << " " << to_string(carre.point.x) << " " << to_string(carre.point.y) 
			<< " " << to_string(total_food) << " ";
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

bool Collector::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_C()) {
		return true;
	}
	initialise_fourmi();
	return false;

}

bool Collector::superposition_fourmi_C() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::collector_overlap( carre.point.x, carre.point.y, x, y);
		return true;
	}
	return false;
}

void Collector::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_diagonale(carre, graphic, couleur);
	if(have_food) {
		Carre carre_food{1, {carre.point.x, 
		carre.point.y}};
		draw_carre_losange(carre_food, graphic);
	}
}

void Collector::ecriture_frmi(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y) << " "
	<< to_string(age) << " ";
	string have_food_string;
	if(have_food==true) {
		have_food_string="true\n";
	} else {
		have_food_string="false\n";
	}
	fichier << have_food_string;
}

void Defensor::initialise_defens(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

bool Defensor::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_D()) {
		return true;
	}
	if(fourmis_in_house_D(countF, carre_fourmiliere)) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Defensor::superposition_fourmi_D() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::defensor_overlap( carre.point.x, carre.point.y, x, y );
		return true;
	}
	return false;
}

bool Defensor::fourmis_in_house_D(unsigned int countF, const Carre& carre_fourmiliere) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::defensor_not_within_home(carre.point.x, carre.point.y,
		countF);
		return true;
	}
	return false;
}

void Defensor::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_grille(carre, graphic, couleur);
}

void Defensor::ecriture_frmi(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y) << " " 
			<< to_string(age) << "\n";
}
	
void Predator::initialise_predat(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

bool Predator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_P()) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Predator::superposition_fourmi_P() {
	if(test_superposition_sans_coord(carre)) {
		cout << message::predator_overlap(carre.point.x, carre.point.y);
		return true;
	}
	return false;
}

void Predator::draw_fourmis(Graphic graphic, Couleur couleur) {
	draw_carre_uniforme(carre, graphic, couleur);
}

void Predator::ecriture_frmi(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y) << " " 
			<< to_string(age) << "\n";
}

void decodage_line_fourmis(string line, unsigned int etat, Collector& collector,
Defensor& defensor, Predator& predator) {
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
