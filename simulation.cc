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

bool Simulation::lecture(char * nom_fichier) {	
    string line;
    bool erreur(false); // détection erreur problème avec t13.txt meilleur manière??
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
		//cout << message::success();
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
			decodage_line_fourmiliere(line, ensemble_fourmiliere, erreur);
			break;
			
		default : exit(0);
	}
}
void Simulation::supprimer_structs() {
		initialise_grid(g_max);
		ensemble_food.clear();
		ensemble_fourmiliere.clear(); // détruit aussi les fourmis??
}
