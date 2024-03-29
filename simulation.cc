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
	enum etat_kill{DEFENSOR, PREDATOR};
	create_food();
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		maj_fourmiliere(i);
		cout << "FOURMILIERE " << i<< endl;
		ensemble_fourmilieres[i].maj_generator(ensemble_food); 
		fourmis_kill(i, DEFENSOR);
		ensemble_fourmilieres[i].action_autres_fourmis(ensemble_food);
		fourmis_kill(i, PREDATOR);
		predator_maj(i);
		
	}
	for(size_t i(0); i < ensemble_fourmilieres.size(); ++i) {
		ensemble_fourmilieres[i].destruction_fourmis(ensemble_food);
		if(ensemble_fourmilieres[i].destruction_fourmiliere()) {
			ensemble_fourmilieres.erase(ensemble_fourmilieres.begin()+i);
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
	int expend(IG);
	if(ensemble_fourmilieres.size() ==1) {
		Carre carre = ensemble_fourmilieres[i].get_carre();
		carre.longeur = ensemble_fourmilieres[i].get_sizeF()+2;
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
		return;
	}					
	bool inf_gauche(true), sup_gauche(true), sup_droite(true), inf_droite(true);
	for(size_t j(0); j < ensemble_fourmilieres.size(); ++j){
		if(i != j) {
			if(inf_gauche) {
				if(!ensemble_fourmilieres[i].test_inf_gauche(ensemble_fourmilieres[j])){
					inf_gauche=false;
				}
			} 
			if(sup_gauche) {
				if(!ensemble_fourmilieres[i].test_sup_gauche(ensemble_fourmilieres[j])){
					sup_gauche=false;
				}
			} 
			if(sup_droite) {
				if(!ensemble_fourmilieres[i].test_sup_droite(ensemble_fourmilieres[j])){
					sup_droite=false;  
				}
			} 
			 if(inf_droite) {
				if(!ensemble_fourmilieres[i].test_inf_droite(ensemble_fourmilieres[j])){
					inf_droite=false;;
				}
			} 
		}
	}
	if(inf_gauche) {
		expend=IG;
	} else if(sup_gauche) {
		expend=SG;
	} else if(sup_droite) {
		expend=SD;
	} else if(inf_droite) {
		expend=ID;
	} else {
		expend = RIEN;
	}	
	ensemble_fourmilieres[i].mise_a_jour(expend);
}

void Simulation::fourmis_kill(unsigned int i, unsigned int etat_kill) {
	for(size_t j(0); j < ensemble_fourmilieres.size(); ++j) {
		if(i!=j) {
			ensemble_fourmilieres[i].fourmi_kill(ensemble_fourmilieres[j], etat_kill);
		}
	}
}

void Simulation::predator_maj(unsigned int i) {
	if(ensemble_fourmilieres[i].get_etat_f()==FREE) {
		vector<Carre> fourmis_infiltres;
		for(size_t j(0); j < ensemble_fourmilieres.size(); ++j) {
			if(i!=j) {
				ensemble_fourmilieres[i].intrusion_fourmi(ensemble_fourmilieres[j],
														  fourmis_infiltres);
			}
		}
		if(fourmis_infiltres.size() == 0) {
			ensemble_fourmilieres[i].predator_in_house();
			return;
		}
		ensemble_fourmilieres[i].deplacement_predator(fourmis_infiltres);
	} else if(ensemble_fourmilieres[i].get_etat_f()==CONSTRAINED) {
		vector<Carre> closest_fourmis;
		for(size_t j(0); j < ensemble_fourmilieres.size(); ++j) {
			if(i!=j) {
				ensemble_fourmilieres[i].closest_fourmi(ensemble_fourmilieres[j],
														  closest_fourmis);
			}
		}
		if(closest_fourmis.size() == 0) {
			ensemble_fourmilieres[i].predator_in_house();
			return;
		}
		ensemble_fourmilieres[i].deplacement_predator(closest_fourmis);
	}
		
}
	
