//simulation.cc
//Rayan Gauderon membre 1: 30%
//Maxime Luyet membre 2: 70%

#include <iostream>
#include <random>

#include "simulation.h"

using namespace std;

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
	unsigned int color(0);
	for(auto& fourmiliere : ensemble_fourmilieres) {
		++color;
		fourmiliere.draw_fourmiliere(color);
		if( color==6) {
			color=0;
		}
		
	}
}

void Simulation::refresh() {
	//PARTIE CREATION DE NOURRITURE
	create_food();
	//PARTIE AJUSTEMENT/DEPLACEMENT FOURMILIERE
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].calcul_sizeF();
		for(size_t j(0); j < ensemble_fourmilieres.size();++j) {
			if( i!=j) { //pas faire le test sur la meme fourmiliere
				if(ensemble_fourmilieres[i].test_fourmiliere_no_mess(
				   ensemble_fourmilieres[j])) {
					//tester sur les autres coins
				}
			} 
		}
		ensemble_fourmilieres[i].expend_restrict();
	
	//PARTIE GENERATOR
	ensemble_fourmilieres[i].maj_generator(); 
	ensemble_fourmilieres[i].create_fourmi();	 
	//nsemble_fourmilieres[i].deplacement_generator();
	//déplacement
	//PARTIE AUTRES FOURMIS
	ensemble_fourmilieres[i].action_autres_fourmis();
	}
	for(auto& fourmiliere : ensemble_fourmilieres) {
		fourmiliere.destruction_fourmis(ensemble_food);
		//meilleur manière pour ajouter food si collector en a??
		if(fourmiliere.destruction_fourmiliere()) {
			//enlever sans changer l'ordre pour les couleurs??
			/*swap(ensemble_fourmilieres[k], ensemble_fourmilieres[ensemble_fourmilieres.size()-1]);
			ensemble_fourmilieres.pop_back();*/
			//supprimer fourmiliere implique son id change??
		}
	}
}

void Simulation::create_food() {
	random_device rd;
	double p(food_rate);
	bernoulli_distribution b(p);
	default_random_engine eng(rd());
	if(b(eng)) {
		unsigned int i(0);
		Carre carre_food{1, {0, 0}};
		Food food(carre_food, val_food);
		while( i < max_food_trial) {
			food.random_food();
			if(superposition_food_with_all(food.get_carre())) {
				++i;
			} else {
				initialise_carre_centre(food.get_carre());
				ensemble_food.push_back(food);
				return;
			}
		}
	}
}
	
bool Simulation::superposition_food_with_all(const Carre& carre_food) {
	if(test_superposition_sans_coord(carre_food)) {
		return true;
	}
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		if(test_superposition_2_carres(ensemble_fourmilieres[i].get_Carre(), carre_food)) {
			return true;
		}
	}
	return false;
}


