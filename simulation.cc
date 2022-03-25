#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


#include "simulation.h"


using namespace std;

Simulation::Simulation(Grid grid, Ensemble_carre ensemble_carre) 
: grid(grid), ensemble_carre(ensemble_carre) {}
void Simulation::lecture(char * nom_fichier)
{	

	
	
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
       //exit(0);
	}
	else {
		//exit(0);
	}	
	//affiche_grid(grid);
}

void Simulation::decodage_ligne(string line){
	
	enum Etat_lecture {NBN, FOOD, NBF,FRMI, NBC, COLLECT, NBD, DEFNS, NBP, PREDAT };
	
	istringstream data(line);
	
	static int etat(NBN);
	static int count(0),total(0);
	unsigned int x, y, age, xg, yg, side, total_food;
	static int countC(0), countD(0), countP(0), nbC, nbD, nbP;
	string have_food;
	Carre carre;
	
	
	switch(etat)
	{
	case NBN:
		data >> total;
		count = 0;
		if(total == 0) {
			etat = NBF;
		} else {
			etat =FOOD;
		}
		//Mettre dans une classe
		//cout << "Nombre nourriture : " << total << endl;
		break;
		
	case FOOD:
		data >> x >> y;
		++count;
		if(count == total) {
			etat = NBF;
		}
		carre={1, {x,y}};
		test_validation_carre(grid, carre);
			
		
		if(!test_superposition(grid, carre, ensemble_carre)) {
				cout << message::food_overlap(x,y);
				std::exit(EXIT_FAILURE);
		}
		initialise_carre(grid,carre);
		ensemble_carre.push_back(carre);
		//cout << "Nourriture " << count << " : " << x << " " << y << endl;
		break;
		
	case NBF:
		data >> total; count=0;
		if(total == 0) {
			exit(EXIT_FAILURE);
		} else {
			etat = FRMI;
		}
		
		//Mettre dans une classe
		break;
		
	case FRMI:
		data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
		++count;

		//Mettre dans une classe
		//Une fois que countC = nbC, on passe a Def
		//Quand Pro est fini, si encore fourmiliere on revient ici
		
	//	cout << "Fourmiliere " << count << " : " << x << " " << y << " " << side << " " << xg << " " << yg << " " << total_food << " " << nbC << " " << nbD << " " << nbP << endl;
		// lecture fichier dans fourmilière
		countC=0; countD=0; countP=0;
		if(nbC!=0) {
			etat=COLLECT ;
			break;
		}
		if(nbD!=0) {
			etat=DEFNS;
			break;
		}
		if(nbP!=0) {
			etat=PREDAT;
			break;
		}
		if(count==total) { break; }
		break;
	
	case COLLECT:
		if(nbC == 0) {
			etat = DEFNS;
			break;
		}
		data >> x >> y >> age >> have_food; ++countC;
		if(countC == nbC) {
			etat = DEFNS;
		}
		//Mettre dans une classe
		//cout << "Collector " << countC << " : " <<  x << " " << y << " " << age << " " << food << endl;
		break;
		
	case DEFNS:
		if(nbD == 0) {
			etat = PREDAT;
			break;
		}
		data >> x >> y >> age;
		++countD;
		if(countD == nbD) {
			etat = PREDAT;
		}
		//Mettre dans une classe
		//cout << "Defensor " << countD << " : " <<  x << " " << y << " " << age << endl;
		break;

	case PREDAT:
		if(nbP == 0) {
			etat = FRMI;
			break;
		}
		data >> x >> y >> age;
		++countP;
		if(countP == nbP) {
			etat = FRMI;
		}
		//Mettre dans une classe
		//cout << "Prédateur " << countP << " : " <<  x << " " << y << " " << age << endl;
		break;
		
	default : exit(0);
	}
}






