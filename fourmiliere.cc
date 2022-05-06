//fourmiliere.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <iostream>
#include <random>
#include <algorithm>

#include "fourmiliere.h"

using namespace std;

Fourmiliere::Fourmiliere(Carre carre, unsigned int nbC, unsigned int nbD, unsigned int nbP,
						unsigned int nbT,unsigned int sizeF)
: carre(carre),  nbC(nbC), nbD(nbD), nbP(nbP), nbT(nbT), sizeF(sizeF), etat_f(FREE) {}

double Fourmiliere::get_total_food() const {
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

Carre Fourmiliere::get_Carre() const {
	return carre;
}

bool Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
												 unsigned int countF, unsigned int i) {
	if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
		cout << message::homes_overlap(i, countF);
		return true;
	}
	return false;
}

bool Fourmiliere::test_fourmiliere_no_mess(const Fourmiliere& autre_fourmiliere) {
	if(test_validation_carre_non_centre(carre)) {
		return true;
	}
	if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
		return true;
	}
	etat_f=FREE;
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

void Fourmiliere::ecriture_fourmiliere(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y)
			<< " " << to_string(carre.longeur);
	ensemble_fourmis[0]->ecriture_frmi(fichier);
	fichier << to_string(nbC) << " " << to_string(nbD) << " " << to_string(nbP) 
	        << "\n\n";
	for(size_t i(1); i < ensemble_fourmis.size(); ++i) {
		ensemble_fourmis[i]->ecriture_frmi(fichier);
		if(i==nbC) {
			fichier << "\n";
		}
		if(i==nbC+nbD and nbD!= 0) {
			fichier << "\n";
		}
		if(i==nbC+nbD+nbP and nbP!=0) {
			fichier << "\n";
		}
	}
}

void Fourmiliere::draw_fourmiliere(unsigned int couleur) {
	unsigned int style(VIDE);
	draw_carre(carre, style, couleur);
	for(const auto& fourmi : ensemble_fourmis) {
		fourmi->draw_fourmis(couleur);
	}
}

void Fourmiliere::calcul_sizeF() {
	sizeF = sqrt(4*(sizeG*sizeG + sizeC*sizeC*nbC + sizeD*sizeD*nbD + 
	sizeP*sizeP*nbP));
}
	
void Fourmiliere::expend_restrict() {
		carre.longeur = sizeF+2;
}

void Fourmiliere::maj_generator() {
	ensemble_fourmis[0]->consommation(nbT);
}

void Fourmiliere::create_fourmi() {
	random_device rd;
	//TRIER FOURMI??
	double total_food = ensemble_fourmis[0]->get_total_food();
	//double p(min(1.0, total_food * birth_rate));
	double p(1);
	bernoulli_distribution b(p);
	default_random_engine eng(rd());
	if(b(eng)) {
		if(etat_f == FREE) {
			if((double)nbC/nbT <= prop_free_collector) { 
				Carre carre_collector{sizeC, {0,0}};
				recherche_espace_libre(carre_collector);
				unsigned int age(0);
				ajouter_fourmis(new Collector(carre_collector, age));
				++nbC; ++nbT;
				return;
			} else if((double)nbD/nbT <= prop_free_defensor) {
				Carre carre_defensor{sizeD, {0,0}};
				recherche_espace_libre(carre_defensor);
				unsigned int age(0);
				ajouter_fourmis(new Defensor(carre_defensor, age));
				++nbD; ++nbT;
				return;
			} else {
				Carre carre_predator{sizeP, {0,0}};
				recherche_espace_libre(carre_predator);
				unsigned int age(0);
				ajouter_fourmis(new Predator(carre_predator, age));
				++nbP; ++nbT;
				return;
			}
		}
		if(etat_f == CONSTRAINED) {
			if((double)nbC/nbT <= prop_constrained_collector) { 
				Carre carre_collector{sizeC, {0,0}};
				recherche_espace_libre(carre_collector);
				unsigned int age(0);
				ajouter_fourmis(new Collector(carre_collector, age));
				++nbC; ++nbT;
				return;
			} else if((double)nbD/nbT <= prop_constrained_defensor) {
				Carre carre_defensor{sizeD, {0,0}};
				recherche_espace_libre(carre_defensor);
				unsigned int age(0);
				ajouter_fourmis(new Defensor(carre_defensor, age));
				++nbD; ++nbT;
				return;
			} else {
				Carre carre_predator{sizeP, {0,0}};
				recherche_espace_libre(carre_predator);
				unsigned int age(0);
				ajouter_fourmis(new Predator(carre_predator, age));
				++nbP; ++nbT;
				return;
			}
		}
	}
}

void Fourmiliere::recherche_espace_libre(Carre& carre_fourmi) {
	do {
	random_device rd;
    uniform_int_distribution<int> distr(2 + carre_fourmi.longeur/2,
    carre.longeur-2-carre_fourmi.longeur/2);
    default_random_engine eng(rd());
    carre_fourmi.point.x = distr(eng) +carre.point.x;
    carre_fourmi.point.y = distr(eng)+carre.point.y;
    } while(test_superposition_sans_coord(carre_fourmi));
     initialise_carre_centre(carre_fourmi);
}	

void Fourmiliere::deplacement_generator() {
	ensemble_fourmis[0]->deplacement_fourmi(carre);
}

void Fourmiliere::action_autres_fourmis() {
	if(ensemble_fourmis[0]->get_end_of_klan()==false) {
		 for(size_t i(1); i < ensemble_fourmis.size(); ++i) {
			ensemble_fourmis[i]->incrementer_age();
			//action
		}
	}
}
	
void Fourmiliere::destruction_fourmis(Ensemble_food& ensemble_food) {
	for(size_t i(1);  i < ensemble_fourmis.size(); ++i) {
		if(ensemble_fourmis[i]->get_age()==bug_life or 
		   ensemble_fourmis[i]->get_end_of_life()==true) {
			  //  ensemble_fourmis[i].erase(ensemble_fourmis.begin() + i);
			//	ensemble_fourmis[i].reset();
			//	swap(ensemble_fourmis[i], ensemble_fourmis[ensemble_fourmis.size()-1]);
			//	ensemble_fourmis.pop_back();
				//meilleur moyen??*/
				--nbT;
		 }	 
	} 
}

bool Fourmiliere::destruction_fourmiliere() {
	if(ensemble_fourmis[0]->get_end_of_klan()==true) {
		return true;
	}
	return false;
}
	
bool decodage_line_fourmiliere(string line, Ensemble_fourmilieres& ensemble_fourmilieres, 
							   unsigned int total, int& etat) {
	istringstream data(line);
	enum Etat_lecture{FRMIL, COLLECT, DEFNS, PREDAT};
	static unsigned int etat_f(FRMIL);
	unsigned int x, y, side, xg, yg, total_food;
	static unsigned int countF(0), countC(0), countD(0), countP(0), count_fourmis(0),
	nbC, nbD, nbP;
	if(etat_f==FRMIL) {
		data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
		unsigned int nbT= 1+nbC+nbD+nbP;
		Carre carre{side, {x, y}};
		unsigned int sizeF= sqrt(4*(sizeG*sizeG + sizeC*sizeC*nbC + sizeD*sizeD*nbD + 
		sizeP*sizeP*nbP));
		Fourmiliere fourmiliere(carre, nbC, nbD, nbP, nbT, sizeF);
		if(test_validation_carre_non_centre(carre)) {
			count_fourmis=0; 
			countF=0; 
			return true; 
		}
		for(size_t i(0); i < ensemble_fourmilieres.size() ; ++i) {
			if(fourmiliere.test_superposition_fourmiliere(ensemble_fourmilieres[i],
			countF, i)) {
				count_fourmis=0; 
				countF=0; 
				return true;
			}
		}
		Carre carre_generator{sizeG, {xg, yg}};
		fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
		if(fourmiliere.test_fourmis(countF, count_fourmis)) {
			count_fourmis=0; 
			countF=0; 
			return true;
		}
		ensemble_fourmilieres.push_back(std::move(fourmiliere));
		++count_fourmis;
		countC=0; countD=0; countP=0;
		if(nbC!=0) {
			etat_f=COLLECT ;
			return false ;
		}
		if(nbD!=0) {
			etat_f=DEFNS; 
			return false;
		}
		if(nbP!=0) {
			etat_f=PREDAT; 
			return false;
		} else {
			count_fourmis=0;
			if(ensemble_fourmilieres.size()==total) {
				countF = 0; 
				etat = 0; 
				return false;
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
		countF = 0; 
		count_fourmis=0; 
		etat = 0;
		return false;
	}
	return false;
}

bool decodage_line_ensemble_fourmis(string line, Fourmiliere *fourmiliere, 
									unsigned int& count_fourmis, unsigned int& countF , 
									unsigned int& etat_f, unsigned int& countC, 
									unsigned int& countD, unsigned int& countP, 
									unsigned int& nbC, unsigned int& nbD, 
									unsigned int& nbP) {
	Carre carre{0, {0, 0}}; Collector collector(carre, 0);
	Defensor defensor(carre, 0); Predator predator(carre, 0);
	switch(etat_f) {
		case 1 :
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Collector(collector));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0 ; 
				countF=0; 
				count_fourmis=0; 
				return true;
			}
			++count_fourmis; ++countC;
			if(countC==nbC  and nbD == 0 and nbP == 0) { 
				etat_f= 0; 
				count_fourmis=0; 
				++countF; 
				break;
			} else if(countC==nbC) { 
				etat_f = 2 ; 
			}
			break;
		case 2 :
			if(nbD==0) { 
				etat_f= 3; 
				break;
			}
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Defensor(defensor));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0; 
				countF=0; count_fourmis=0; 
				return true;
			}
			++count_fourmis; 
			++countD;
			if(countD==nbD and nbP==0) { 
				etat_f=0 ; 
				count_fourmis=0; 
				++countF; 
				break; 
			} else if (countD ==nbD) { 
				etat_f= 3; 
			}
			break;
		case 3 :
			if(nbP==0) { 
				etat_f= 0 ;
				count_fourmis=0; 
				++countF; 
				break; 
			}
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Predator(predator));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0; 
				countF=0; 
				count_fourmis=0; 
				return true;
			}
			++count_fourmis; 
			++countP;
			if(countP==nbP) {
				count_fourmis=0; 
				++countF; 
				etat_f= 0;
			}
			break;
		default :
			exit(0);
	}
	return false;
}
