//simulation.cc
//Rayan Gauderon membre 1: 30%
//Maxime Luyet membre 2: 70%

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "simulation.h"


using namespace std;
unsigned int Simulation::get_nb_food() const {
	return ensemble_food.size();
}

unsigned int Simulation::get_ensemble_fourmilieres_size() const {
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
    bool erreur(false);
    ifstream fichier(nom_fichier);
     
    if(!fichier.fail()) {
        while(getline(fichier >> ws,line)) {	
			
			if(line[0]=='#')  continue;  
			decodage_ligne(line, erreur);
			/*if(erreur) {
				cout << "ERREUR" << endl;
				//supprimer_structs();
				fichier.close(); //probleme passe autre fichier texte regler vendredi
				return;*/
			//}
        }
	}
	cout << message::success();
	//supprimer_structs();
//	fichier.close(); 
	//cout << ensemble_fourmilieres.size() << endl;
}

void Simulation::decodage_ligne(string& line, bool& erreur) {
	istringstream data(line);
	enum Etat_lecture {NBN, FOOD, NBF, FRMIL, SORTIE};
	static int etat(NBN);
	static unsigned int count(0), total(0);
	switch(etat) {
		case NBN :
			total = 0;
			data >> total; count = 0;
			if(total == 0) {
				etat = NBF;
			} else {
				etat = FOOD;
			}
			break;
		
		case FOOD :
			decodage_line_food(line, ensemble_food, erreur);
			++count;
			if(count == total) {
				etat = NBF;
			} 
			break;
			
		case NBF :
			data >> total; count = 0;
			if(total == 0) {
				etat = SORTIE;
				
				break;
			} else {
				etat = FRMIL;
			}
			break;
		
		case FRMIL :
			decodage_line_fourmiliere(line, ensemble_fourmilieres, erreur);
			//if(ensemble_fourmilieres.size()==total) {
				//ensemble_fourmilieres.clear(); 
				 //probleme avec la derniere fourmilierer
				//etat = SORTIE;
			//}
			break;
		
		case SORTIE :
			total = 0;
			count = 0;
			etat = NBN;
			break;
			
		default : exit(0);
	}
}

/*void Simulation::supprimer_structs() {
		supprimer_grid();
		initialise_grid(g_max);
		ensemble_food.clear();
		for(auto& fourmiliere : ensemble_fourmilieres) {
			fourmiliere.supprimer_fourmis();
			
		}
		//ensemble_fourmilieres.clear();
}*/

void Simulation::draw_simulation(Graphic graphic) {
	initialise_ensemble_couleurs();
	graphic.draw_grille();
	for(auto& food : ensemble_food) {
		food.draw_food(graphic);
		
	}
	unsigned int i(0);
	for(auto& fourmiliere : ensemble_fourmilieres) {
		fourmiliere.draw_fourmiliere(graphic, ensemble_couleurs[i]);
		++i;
		if( i==6) { //refaire la boucle de couleur
			i=0;
		}
	}
}

void Simulation::initialise_ensemble_couleurs() {
	Couleur rouge{1.0, 0.0, 0.0};
	Couleur green{0.0, 1.0, 0.0};
	Couleur blue{0.0, 0.0, 1.0};
	Couleur jaune{1.0, 1.0, 0.0};
	Couleur magenta{1.0, 0.0, 1.0};
	Couleur cyan{0.0, 1.0, 1.0};
	ensemble_couleurs.push_back(rouge); 
	ensemble_couleurs.push_back(green); 
	ensemble_couleurs.push_back(blue); 
	ensemble_couleurs.push_back(jaune); 
	ensemble_couleurs.push_back(magenta); 
	ensemble_couleurs.push_back(cyan); 
}
