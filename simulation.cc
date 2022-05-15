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
	for(auto& fourmiliere : ensemble_fourmilieres) {
		fourmiliere.draw_fourmiliere();
	}
}

void Simulation::refresh() {
	//PARTIE CREATION DE NOURRITURE
	create_food();
	//PARTIE AJUSTEMENT/DEPLACEMENT FOURMILIERE
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].calcul_sizeF();
		//test_expend_fourmiliere(i);
	//PARTIE GENERATOR
	//ensemble_fourmilieres[i].maj_generator(); 
	//ensemble_fourmilieres[i].create_fourmi();	 
	ensemble_fourmilieres[i].deplacement_generator(ensemble_food);
	//déplacement
	//PARTIE AUTRES FOURMIS
	ensemble_fourmilieres[i].action_autres_fourmis(ensemble_food);
	}
	/*for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].destruction_fourmis(ensemble_food);
		if(ensemble_fourmilieres[i].destruction_fourmiliere()) {
			ensemble_fourmilieres.erase(ensemble_fourmilieres.begin()+i);
		}
	}*/
}

void Simulation::create_food() {
	random_device rd;
	double p(food_rate);
	bernoulli_distribution b(p);
	default_random_engine eng(rd());
	if(b(eng)) {
		unsigned int i(0);
		Carre carre_food{1, {0, 0}};
		Food food(carre_food);
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
		if(test_superposition_2_carres(ensemble_fourmilieres[i].get_carre(), carre_food)) {
			return true;
		}
	}
	return false;
}

bool Simulation::test_expend_fourmiliere(unsigned int i) {
	unsigned int k(0);
	for(size_t j(0); j < ensemble_fourmilieres.size(); ++j) {
		if(i != j) {
			ensemble_fourmilieres[i].test_expend(ensemble_fourmilieres[j], k);
				
			/*Carre carre1 = ensemble_fourmilieres[i].get_carre();
			unsigned int longeur = carre1.longeur;
			Carre carre2 = ensemble_fourmilieres[j].get_carre();
			if(ensemble_fourmilieres[i].superposition_inf_gauche(carre2, longeur, k)) {
			
			if(ensemble_fourmilieres[i].superposition_sup_gauche(carre2, longeur, k)) {
				return true;
				}*/
			}
		}
	cout << k << endl;
	ensemble_fourmilieres[i].expend(k);
}
	//return false;
/*bool Simulation::test_fourmiliere(unsigned int i) {
	cout << "I : " << i << endl;
	unsigned int k(0);
	unsigned int taille_f = ensemble_fourmilieres.size();
	if(taille_f == 1) {
		if(ensemble_fourmilieres[i].test_inf_gauche()) {
			if(ensemble_fourmilieres[i].test_sup_gauche()) {
				if(ensemble_fourmilieres[i].test_sup_droite()) {
					if(ensemble_fourmilieres[i].test_inf_droite()) {
						return true;
					}
				}
			}
		}
	} else {
	for(size_t j(0); j < ensemble_fourmilieres.size(); ++j) {
			if(i != j) {
				cout << "J : " << j << endl;
				Carre carre = ensemble_fourmilieres[j].get_carre();
				ensemble_fourmilieres[i].test_inf_gauche(carre, k);
					if(k==0) {
				   ensemble_fourmilieres[i].test_sup_gauche(carre, k);
					//return true;
				}
			
				//	}
				//} 
			}
					
			} 
		}
	
	ensemble_fourmilieres[i].expend_restrict(k);
	//return false;
}*/

