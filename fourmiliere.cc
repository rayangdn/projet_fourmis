#include <cstdlib>
#include <iostream>
#include <fstream>
//fourmiliere.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "fourmiliere.h"

using namespace std;

Fourmiliere::Fourmiliere(Carre carre, unsigned int nbC, unsigned int nbD,
unsigned int nbP)
: carre(carre),  nbC(nbC), nbD(nbD), nbP(nbP) {}

void Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
unsigned int countF, unsigned int i) {
	if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
		cout << message::homes_overlap(i, countF);
		exit(EXIT_FAILURE);
	}
}

void decodage_line_fourmiliere(string line, unsigned int total,
Ensemble_fourmiliere& ensemble_fourmiliere) {
	istringstream data(line);
	enum Etat_lecture{FRMIL, COLLECT, DEFNS, PREDAT};
	static unsigned int etat(FRMIL);
	static unsigned int countF(0), countC(0), countD(0), countP(0), count_fourmis(0),
	nbC, nbD, nbP;
	unsigned int x, y, side, xg, yg, total_food;
	if(etat==FRMIL) {
		data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
		Carre carre{side, {x, y}};
		test_validation_carre_non_centre(carre);
		Fourmiliere fourmiliere(carre, nbC, nbD, nbP);
		for(size_t i(0); i < ensemble_fourmiliere.size() ; ++i) {
			fourmiliere.test_superposition_fourmiliere(ensemble_fourmiliere[i],
			countF, i);
		}
		Carre carre_generator{sizeG, {xg, yg}};
		test_validation_carre_centre(carre_generator);
		fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
		fourmiliere.test_fourmis(countF, count_fourmis);
		++count_fourmis;
		ensemble_fourmiliere.push_back(std::move(fourmiliere));
		countC=0; countD=0; countP=0;
		if(nbC!=0) {
			etat=COLLECT ;
			return;
			}
		if(nbD!=0) {
			etat=DEFNS;
			return;
			}
		if(nbP!=0) {
			etat=PREDAT;
			return;
		}
	} 
	Carre carre{0, {0, 0}}; Collector collector(carre, 0, "");
	Defensor defensor(carre, 0); Predator predator(carre, 0);
	switch(etat) {
		case COLLECT :
			decodage_line_fourmis(line, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF].ajouter_fourmis(new Collector(collector));
			ensemble_fourmiliere[countF].test_fourmis(countF, count_fourmis);
			++count_fourmis;
			++countC;
			if(countC==nbC) {
				etat=DEFNS;
			}
			break;
		
		case DEFNS :
			decodage_line_fourmis(line, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF].ajouter_fourmis(new Defensor(defensor));
			ensemble_fourmiliere[countF].test_fourmis(countF, count_fourmis);
			++count_fourmis;;
			++countD;
			if(countD==nbD) {
				etat=PREDAT;
			}
			break;
			
		case PREDAT :
			decodage_line_fourmis(line, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF].ajouter_fourmis(new Predator(predator));
			ensemble_fourmiliere[countF].test_fourmis(countF, count_fourmis);
			++count_fourmis;;
			++countP;
			if(countP==nbP) {
				etat=FRMIL;
				count_fourmis=0;
				++countF;
			}
			break;
	}
}
	
void Fourmiliere::ajouter_fourmis(Fourmi* nouveau) {
	if(nouveau!= nullptr) {
		ensemble_fourmis.push_back(unique_ptr<Fourmi>(nouveau));
	}
}

void Fourmiliere::test_fourmis(unsigned  int countF, unsigned int i) {
	ensemble_fourmis[i]-> test_chaque_fourmi(countF, carre);
}
