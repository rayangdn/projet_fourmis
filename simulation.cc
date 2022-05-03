//simulation.cc
//Rayan Gauderon membre 1: 30%
//Maxime Luyet membre 2: 70%

#include <iostream>
#include <random>

#include "simulation.h"

using namespace std;

const int MIN_FOOD = 1;
const int MAX_FOOD = g_max-2;

unsigned int Simulation::get_nb_food() const {
	return ensemble_food.size();
}

unsigned int Simulation::get_nb_fourmiliere() const {
	return ensemble_fourmilieres.size();
}

double Simulation::get_total_food(int i) const  {
	return ensemble_fourmilieres[i].get_total_food();
}

unsigned int Simulation::get_nbC(int i) const {
	return ensemble_fourmilieres[i].get_nbC();
}

unsigned int Simulation::get_nbD(int i) const {
	return ensemble_fourmilieres[i].get_nbD();
}

unsigned int Simulation::get_nbP(int i) const {
	return ensemble_fourmilieres[i].get_nbP();
}

void Simulation::lecture(string nom_fichier) {	
    string line;
    ifstream fichier(nom_fichier);
    if(!fichier.fail()) {
        while(getline(fichier >> ws,line)) {	
			if(line[0]=='#')  continue;  
			if(decodage_line(line)) {
				supprimer_structs();
				fichier.close();
				return;
			}
        }
	}
	cout << message::success();
	fichier.close(); 
}

bool Simulation::decodage_line(string& line) {
	istringstream data(line);
	enum Etat_lecture {NBN, FOOD, NBF, FRMIL};
	static int etat(NBN);
	static unsigned int count(0), total(0);
	switch(etat) {
		case NBN :
			data >> total; count = 0;
			if(total == 0) {
				etat = NBF;
			} else {
				etat = FOOD;
			}
			break;
		case FOOD :
			++count;
			if(decodage_line_food(line, ensemble_food)) {
				etat = NBN;
				return true;
			}
			if(count == total) {
				etat = NBF;
			} 
			break;
		case NBF :
			data >> total; count = 0;
			if(total == 0) {
				etat = NBN;
				break;
			} else {
				etat = FRMIL;
			}
			break;
		case FRMIL :
			if(decodage_line_fourmiliere(line, ensemble_fourmilieres, total, etat)) {
				etat = NBN;
				return true;
			}
			break;		
		default : exit(0);
	}
	return false;
}

void Simulation::supprimer_structs() {
	supprimer_grid();
	initialise_grid(g_max);
	ensemble_food.clear();
	for(auto& fourmiliere : ensemble_fourmilieres) {
		fourmiliere.supprimer_fourmis();	
	}
	ensemble_fourmilieres.clear();
}

void Simulation::ecriture_fichier(ofstream& fichier) const {
	fichier << to_string(ensemble_food.size()) << "\n\n" ;
	for(size_t i(0); i < ensemble_food.size(); ++i) {
		ensemble_food[i].ecriture_food(fichier);
	}
	fichier << "\n" <<  to_string(ensemble_fourmilieres.size()) << "\n";
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].ecriture_fourmiliere(fichier);
	}
}
bool Simulation::superposition_food_with_all(const Carre& carre_food) {
	if(test_superposition_sans_coord(carre_food)) {
		return true;
	}
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		if(test_superposition_2_carres(ensemble_fourmilieres[i].carre, carre_food)) {
			return true;
		}
	}
	return false;
}
void Simulation::draw_simulation() {
	for(auto& food : ensemble_food) {
		food.draw_food(); 
	}
	unsigned int i(0);
	for(auto& fourmiliere : ensemble_fourmilieres) {
		++i;
		fourmiliere.draw_fourmiliere(i);
		if( i==6) { //refaire la boucle de couleur
			i=0;
		}
		
	}
}

void Simulation::refresh() {
	create_food();
}

void Simulation::create_food() {
	random_device rd;
	double p(food_rate);
	bernoulli_distribution b(p);
	default_random_engine eng(rd());
	if(b(eng)) {
		unsigned int i(0);
		while( i < max_food_trial) {
			Point point_food;
			Carre carre_food{1, point_food};
			random_food(carre_food);
			Food food(carre_food, val_food);
			if(superposition_food_with_all(carre_food)) {
				++i;
			} else {
				food.draw_food();
				initialise_carre_centre(carre_food);
				ensemble_food.push_back(food);
				return;
			}
		}
	}
}
void Simulation::random_food(Carre& carre) {
	random_device rd;
    uniform_int_distribution<int> distr(MIN_FOOD, MAX_FOOD);
    default_random_engine eng(rd());
    carre.point.x = distr(eng);
    carre.point.y = distr(eng);
}
	


