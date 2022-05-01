//simulation.cc
//Rayan Gauderon membre 1: 30%
//Maxime Luyet membre 2: 70%

#include <iostream>

#include "simulation.h"

using namespace std;

unsigned int Simulation::get_nb_food() const {
	return ensemble_food.size();
}

unsigned int Simulation::get_nb_fourmiliere() const {
	return ensemble_fourmilieres.size();
}

unsigned int Simulation::get_total_food(int i) const  {
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

	


