#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "simulation.h"

using namespace std;

void Simulation::lecture(char * nom_fichier) {	
    string line;
    ifstream fichier(nom_fichier); 
    if(!fichier.fail()) 
    {
        while(getline(fichier >> ws,line)) 
        {
			if(line[0]=='#')  continue;  
       
			decodage_ligne(line);
        }
		cout << message::success();
	}
}

void Simulation::decodage_ligne(string line) {
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
			decodage_line_food(line, ensemble_food);
			++count;
			if(count == total) {
				etat = NBF;
			} 
			break;
			
		case NBF :
			data >> total; count = 0;
			if(total == 0) {
				exit(EXIT_FAILURE);
			} else {
				etat = FRMIL;
			}
			break;
		
		case FRMIL :
			decodage_line_fourmiliere(line, total, ensemble_fourmiliere);
			break;
			
		default : exit(0);
	}
}

#endif
