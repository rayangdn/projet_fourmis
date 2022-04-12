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
unsigned int Simulation::get_Nb_food() const {
	return ensemble_food.size();
}
bool Simulation::lecture(char * nom_fichier) {	
    string line;
    bool erreur(false);
    ifstream fichier(nom_fichier); 
    if(!fichier.fail()) 
    {
        while(getline(fichier >> ws,line)) 
        {
			if(line[0]=='#')  continue;  
       
			decodage_ligne(line, erreur);
			if(erreur) {
				return false;
			}
        }
	}
	return true;
}

void Simulation::decodage_ligne(string line, bool& erreur) {
	istringstream data(line);
	enum Etat_lecture {NBN, FOOD, NBF, FRMIL};
	static int etat(NBN);
	static int count(0), total(0);
	switch(etat) {
		case NBN :
			data >> total; count = 0;
			if(total == 0) {
				
				etat = NBF;
			} else {
				etat =FOOD;
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
				break;
			} else {
				etat = FRMIL;
			}
			break;
		
		case FRMIL :
			decodage_line_fourmiliere(line, ensemble_fourmilieres, erreur);
			break;
			
		default : exit(0);
	}
}

void Simulation::supprimer_structs() {
		initialise_grid(g_max);
		ensemble_food.clear();
		ensemble_fourmilieres.clear(); // détruit aussi les fourmis??
}

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
