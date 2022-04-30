//fourmiliere.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <cstdlib>
#include <iostream>
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

bool Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
unsigned int countF, unsigned int i) {
	if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
		cout << message::homes_overlap(i, countF);
		return true;
	}
	return false;
}
	
void Fourmiliere::ajouter_fourmis(Fourmi* nouveau) {
	
	if(nouveau!= nullptr) {
		ensemble_fourmis.push_back(unique_ptr<Fourmi>(nouveau));
	}
}

bool Fourmiliere::test_fourmis(unsigned  int countF, unsigned int i) {
	if(ensemble_fourmis[i]->test_chaque_fourmi(countF, carre)) {
		return true;
	}
	return false;
}

void Fourmiliere::supprimer_fourmis() {
	for(auto& fourmi : ensemble_fourmis) {
		ensemble_fourmis.pop_back();
		fourmi.reset();
	}
}

void Fourmiliere::draw_fourmiliere(Graphic graphic, Couleur couleur) {
	draw_carre_vide(carre, graphic, couleur);
	for(const auto& fourmi : ensemble_fourmis) {
		fourmi->draw_fourmis(graphic, couleur);
	}
}

void Fourmiliere::ecriture_fourmiliere(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y)
			<< " " << to_string(carre.longeur);
	ensemble_fourmis[0]->ecriture_frmi(fichier);
	fichier << to_string(nbC) << " " << to_string(nbD) << " " << to_string(nbP) 
	 << "\n\n" ;
	 static unsigned int j(0), k(0), l(0);
	for(size_t i(1); i < ensemble_fourmis.size(); ++i) {
		ensemble_fourmis[i]->ecriture_frmi(fichier);
		++j;
		if(j == nbC) {
			fichier << "\n" ;
			j = 0;
		}
		if(k == nbD and j != nbC) {
			fichier << "\n" ;
			k = 0;
		}
		if(l == nbP and j!=nbC and l!= nbD) {
			fichier << "\n" ;
			l = 0;
		}
	}
}
	

bool decodage_line_fourmiliere(string line, Ensemble_fourmilieres& ensemble_fourmilieres, 
unsigned int total, int& etat) {
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
		if(test_validation_carre_non_centre(carre)) {
			count_fourmis=0; countF=0; return true;
		}
		for(size_t i(0); i < ensemble_fourmilieres.size() ; ++i) {
			if(fourmiliere.test_superposition_fourmiliere(ensemble_fourmilieres[i],
			countF, i)) {
				count_fourmis=0; countF=0; return true;
			}
		}
		Carre carre_generator{sizeG, {xg, yg}};
		fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
		if(fourmiliere.test_fourmis(countF, count_fourmis)) {
			count_fourmis=0; countF=0; return true;
		}
		ensemble_fourmilieres.push_back(std::move(fourmiliere));
		++count_fourmis;
		countC=0; countD=0; countP=0;
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
				countF = 0; etat = 0; return false;
			}
		}
		return false;
	} 
	if(decodage_line_ensemble_fourmis(line, &ensemble_fourmilieres[countF], count_fourmis, 
	countF, etat_f, countC, countD, countP, nbC, nbD, nbP)) {
		return true;
	}
	if(ensemble_fourmilieres.size()==total and countC==nbC and countD==nbD
	  and countP==nbP) {
		countF = 0; count_fourmis=0; etat = 0;
		return false;
	}
	return false;
}
bool decodage_line_ensemble_fourmis(std::string line, Fourmiliere *fourmiliere, 
unsigned int& count_fourmis, unsigned int& countF , unsigned int& etat_f, 
unsigned int& countC, unsigned int& countD, unsigned int& countP, 
unsigned int& nbC, unsigned int& nbD, unsigned int& nbP) {
	Carre carre{0, {0, 0}}; Collector collector(carre, 0, "");
	Defensor defensor(carre, 0); Predator predator(carre, 0);
	switch(etat_f) {
		case 1 :
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Collector(collector));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0 ; countF=0; count_fourmis=0; return true;
			}
			++count_fourmis; ++countC;
			if(countC==nbC  and nbD == 0 and nbP == 0) { 
				etat_f= 0; count_fourmis=0; ++countF; break;
			} else if(countC==nbC) { etat_f = 2 ; }
			break;
		case 2 :
			if(nbD==0) { etat_f= 3; break;}
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Defensor(defensor));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0; countF=0; count_fourmis=0; return true;
			}
			++count_fourmis; ++countD;
			if(countD==nbD and nbP==0) { 
				etat_f=0 ; count_fourmis=0; ++countF; break; 
			} else if (countD ==nbD) { etat_f= 3; }
			break;
		case 3 :
			if(nbP==0) { etat_f= 0 ; count_fourmis=0; ++countF; break; }
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Predator(predator));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0; countF=0; count_fourmis=0; return true;
			}
			++count_fourmis; ++countP;
			if(countP==nbP) {
				count_fourmis=0; ++countF; etat_f= 0;
			}
			break;
		default :
			exit(0);
	}
	return false;
}

