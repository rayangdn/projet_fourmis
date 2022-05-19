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
		maj_fourmiliere(i);
	//PARTIE GENERATOR
		ensemble_fourmilieres[i].maj_generator(ensemble_food); 
	//PARTIE AUTRES FOURMIS
		//ensemble_fourmilieres[i].action_autres_fourmis(ensemble_food);
		defensor_kill_collector(i);
	}
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].destruction_fourmis(ensemble_food);
		if(ensemble_fourmilieres[i].destruction_fourmiliere()) {
			//ensemble_fourmilieres.erase(ensemble_fourmilieres.begin()+i);
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
		if(test_superposition_2_carres_non_centre(ensemble_fourmilieres[i].get_carre(), carre_food)) {
			return true;
		}
	}
	return false;
}

void Simulation::maj_fourmiliere(unsigned int i) {
	ensemble_fourmilieres[i].calcul_sizeF();
	enum Expend_case{IG, SG, SD, ID, RIEN};
	int expend(RIEN);
	if(ensemble_fourmilieres.size() ==1) {
		Carre carre = ensemble_fourmilieres[i].get_carre();
		if(not(test_validation_inf_gauche(carre))) {
			expend = IG;
		} else if(not(test_validation_sup_gauche(carre))) {
			expend = SG;
		} else if(not(test_validation_sup_droite(carre))) {
			expend = SD;
		} else if(not(test_validation_inf_droite(carre))) {
			expend =ID;
		} else {
			expend = RIEN;
		}
		ensemble_fourmilieres[i].mise_a_jour(expend);
	}					
	int k(0); int l(0); int m(0); int n(0);
	for(size_t j(0); j < ensemble_fourmilieres.size(); ++j){
		if(i != j) {
			if(k==0) {
				if(ensemble_fourmilieres[i].test_inf_gauche(ensemble_fourmilieres[j])){
					expend=IG; s
					//cout << "IG"<< endl;
				} else {
					k=1;
				}
			} 
			if( m==0) {
				if(ensemble_fourmilieres[i].test_sup_gauche(ensemble_fourmilieres[j])){
					expend=SG;
					//cout << "SG"<< endl;
				} else {
					m=1;
				}
			} 
			if(l==0) {
				if(ensemble_fourmilieres[i].test_sup_droite(ensemble_fourmilieres[j])){
					expend=SD;
					//cout << "SD"<< endl;
				} else {
					l=1;
				}
			} 
			 if(n==0) {
				//
				if(ensemble_fourmilieres[i].test_inf_droite(ensemble_fourmilieres[j])){
					expend=ID;
				//	cout << "ID"<< endl;
				} else {
					n=1;
				}
				
			} 
			if (k==1 and l==1 and m==1 and n==1) {
				expend = RIEN;
				//cout << "ZERO"<< endl;
			}	
		}
	}
	ensemble_fourmilieres[i].mise_a_jour(expend);
}

void Simulation::defensor_kill_collector(unsigned int i) {
}

