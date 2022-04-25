//fourmiliere.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <cstdlib>
#include <iostream>
#include <fstream>
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

unsigned int Fourmiliere::get_total_food() const {
	return ensemble_fourmis[0]->get_total_food(); //par def generator est la fourmi 0
}
unsigned int Fourmiliere::get_nbC() const {
	return nbC;
}
unsigned int Fourmiliere::get_nbD() const {
	return nbD;
}
unsigned int Fourmiliere::get_nbP() const {
	return nbP;
}

void Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
unsigned int countF, unsigned int i, bool& erreur) {
	if(erreur==false) {
		if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
			cout << message::homes_overlap(i, countF);
			erreur = true;
		}
	}
}
	
void Fourmiliere::ajouter_fourmis(Fourmi* nouveau) {
	
	if(nouveau!= nullptr) {
		ensemble_fourmis.push_back(unique_ptr<Fourmi>(nouveau));
	}
}

void Fourmiliere::test_fourmis(unsigned  int countF, unsigned int i, bool& erreur) {
	ensemble_fourmis[i]->test_chaque_fourmi(countF, carre, erreur);
}

void Fourmiliere::supprimer_fourmis() {
	for(auto& fourmi : ensemble_fourmis) {
		ensemble_fourmis.pop_back();
		fourmi.reset();
	}
}

void Fourmiliere::draw_fourmiliere(Graphic graphic, Couleur couleur) {
	draw_carre_fourmiliere(carre, graphic, couleur);
	for(const auto& fourmi : ensemble_fourmis) {
		fourmi->draw_fourmis(graphic, couleur);
	}
}

bool decodage_line_fourmiliere(string line, Ensemble_fourmilieres& ensemble_fourmilieres, 
bool& erreur, unsigned int total) {
	istringstream data(line);
	enum Etat_lecture{FRMIL, COLLECT, DEFNS, PREDAT};
	static unsigned int etat_f(FRMIL);
	static unsigned int countF(0), countC(0), countD(0), countP(0), count_fourmis(0),
	nbC, nbD, nbP;
	unsigned int x, y, side, xg, yg, total_food;
	if(etat_f==FRMIL) {
		data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
		Carre carre{side, {x, y}};
		Fourmiliere fourmiliere(carre, nbC, nbD, nbP);
		test_validation_carre_non_centre(carre, erreur);
		for(size_t i(0); i < ensemble_fourmilieres.size() ; ++i) {
			fourmiliere.test_superposition_fourmiliere(ensemble_fourmilieres[i],
			countF, i, erreur);
		}
		Carre carre_generator{sizeG, {xg, yg}};
		fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
		fourmiliere.test_fourmis(countF, count_fourmis, erreur);
		ensemble_fourmilieres.push_back(std::move(fourmiliere));
		++count_fourmis;
		countC=0; countD=0; countP=0;
		if(erreur==true) { 
			count_fourmis=0; countF=0; return true;
		}
		if(nbC!=0) {
			etat_f=COLLECT ; return false ;
		}
		if(nbD!=0) {
			etat_f=DEFNS; return false;
		}
		if(nbP!=0) {
			etat_f=PREDAT; return false;
		} else {
			count_fourmis=0;
			if(ensemble_fourmilieres.size()==total) {
				countF = 0; return true;
			}
		}
	return false;
	} 
	Carre carre{0, {0, 0}}; Collector collector(carre, 0, "");
	Defensor defensor(carre, 0); Predator predator(carre, 0);
	switch(etat_f) {
		case COLLECT :
			decodage_line_fourmis(line, etat_f, collector, defensor, predator, erreur);
			ensemble_fourmilieres[countF].ajouter_fourmis(new Collector(collector));
			ensemble_fourmilieres[countF].test_fourmis(countF, count_fourmis, erreur);
			++count_fourmis; ++countC;
			if(erreur==true) {
				etat_f = FRMIL; countF=0; count_fourmis=0; break; 
			}
			if(countC==nbC  and nbD == 0 and nbP == 0) { 
				etat_f=FRMIL; count_fourmis=0; ++countF;  break;
			} else if(countC==nbC) { etat_f =DEFNS; }
			break;
		case DEFNS :
			if(nbD==0) { etat_f=PREDAT; break;}
			decodage_line_fourmis(line, etat_f, collector, defensor, predator, erreur);
			ensemble_fourmilieres[countF].ajouter_fourmis(new Defensor(defensor));
			ensemble_fourmilieres[countF].test_fourmis(countF, count_fourmis, erreur);
			++count_fourmis; ++countD;
			if(erreur==true) {
				etat_f = FRMIL; countF=0; count_fourmis=0; break; 
			}
			if(countD==nbD and nbP==0) { 
				etat_f=FRMIL; count_fourmis=0; ++countF; break; 
			} else if (countD ==nbD) { etat_f=PREDAT; }
			break;
		case PREDAT :
			if(nbP==0) { etat_f=FRMIL; count_fourmis=0; ++countF; break; }
			decodage_line_fourmis(line, etat_f, collector, defensor, predator, erreur);
			ensemble_fourmilieres[countF].ajouter_fourmis(new Predator(predator));
			ensemble_fourmilieres[countF].test_fourmis(countF, count_fourmis, erreur);
			++count_fourmis; ++countP;
			if(erreur==true) {
				etat_f = FRMIL; countF=0; count_fourmis=0; break; 
			}
			if(countP==nbP) {
				count_fourmis=0; ++countF; etat_f=FRMIL;
			}
			break;
		default :
			exit(0);
	}
	if(ensemble_fourmilieres.size()==total and countC==nbC and countD==nbD  and countP==nbP) {
		countF = 0; count_fourmis=0; return true;
	}
	return false;
}

