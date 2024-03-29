//fourmiliere.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <iostream>
#include <random>
#include <algorithm>

#include "fourmiliere.h"

using namespace std;

Fourmiliere::Fourmiliere(Carre carre, unsigned int nbC, unsigned int nbD, unsigned int nbP,
						unsigned int nbT,unsigned int sizeF, unsigned int color)
: carre(carre),  nbC(nbC), nbD(nbD), nbP(nbP), nbT(nbT), sizeF(sizeF), 
  color(color), etat_f(FREE) {}

unsigned int Fourmiliere::get_etat_f() const {
	return etat_f;
}

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

unsigned int Fourmiliere::get_sizeF() const {
	return sizeF;
}

Carre Fourmiliere::get_carre() const {
	return carre;
}

bool Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
												 unsigned int countF, unsigned int i) {
	if(test_superposition_2_carres_non_centre(carre, autre_fourmiliere.carre)) {
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

void Fourmiliere::ajouter_fourmis(Fourmi* nouveau, unsigned int type) {
	if(nouveau!= nullptr) {
		if(type==0) {
			ensemble_fourmis.insert(ensemble_fourmis.begin()+nbC+1, unique_ptr<Fourmi>(nouveau));
		}
		if(type==1) {
			ensemble_fourmis.insert(ensemble_fourmis.begin()+nbC+nbD+1, unique_ptr<Fourmi>(nouveau));
		}
		if(type==2) {
			ensemble_fourmis.push_back(unique_ptr<Fourmi>(nouveau));
		}	
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
	}
	fichier << "\n";
}

void Fourmiliere::draw_fourmiliere() {
	unsigned int style(VIDE);
	draw_carre(carre, style, color);
	for(const auto& fourmi : ensemble_fourmis) {
	
		fourmi->draw_fourmis(color);
	}
}

void Fourmiliere::calcul_sizeF() {
	sizeF = sqrt(4*(sizeG*sizeG + sizeC*sizeC*nbC + sizeD*sizeD*nbD + 
	sizeP*sizeP*nbP));
}

bool Fourmiliere::test_inf_gauche(Fourmiliere& F) {		
	Carre test;
	test.longeur = sizeF + 2;
	test.point = carre.point;
	if(not(test_superposition_2_carres_non_centre(test, F.carre)) 
	   and not(test_validation_inf_gauche(test))) {
		return true;
	} else {
		return false;
	}
}

bool Fourmiliere::test_sup_gauche(Fourmiliere& F) {			//OK?
	Carre test;
	test.longeur = sizeF + 2;
	test.point.x = carre.point.x;
	test.point.y = carre.point.y  + carre.longeur-test.longeur;;
	if(not(test_superposition_2_carres_non_centre(test, F.carre)) 
	   and not(test_validation_sup_gauche(test))) {
		return true;
	} else {
		return false;
	}
}

bool Fourmiliere::test_sup_droite(Fourmiliere& F) { 			//OK?
	Carre test;
	test.longeur = sizeF + 2;
	test.point.x = carre.point.x  + carre.longeur-test.longeur;;
	test.point.y = carre.point.y  + carre.longeur-test.longeur;;
	if(not(test_superposition_2_carres_non_centre(test, F.carre)) 
	   and not(test_validation_sup_droite(test))) {
		return true;
	} else {
		return false;
	}
}

bool Fourmiliere::test_inf_droite(Fourmiliere& F) {			//OK?
	Carre test;
	test.longeur = sizeF + 2;
	test.point.x = carre.point.x + carre.longeur-test.longeur;
	test.point.y = carre.point.y;
	if(not(test_superposition_2_carres_non_centre(test, F.carre)) 
	   and not(test_validation_inf_droite(test))){
		return true;
	} else {
		return false;
	}
}

void Fourmiliere::mise_a_jour(int k) {
	if(k== 0){
		carre.longeur = sizeF+2;
		etat_f = FREE;
	}
	else if(k == 1){
		etat_f = FREE;
		unsigned int longeur = carre.longeur;
		carre.longeur = sizeF+2;
		carre.point.y -= carre.longeur-longeur;
	}
	else if(k== 2){
		etat_f = FREE;
		unsigned int longeur = carre.longeur;
		carre.longeur = sizeF+2;
		carre.point.x -= carre.longeur-longeur;
		carre.point.y -= carre.longeur-longeur;
		
	}
	else if(k == 3){
		etat_f = FREE;
		unsigned int longeur = carre.longeur;
		carre.longeur = sizeF+2;
		carre.point.x -= carre.longeur-longeur;
	}
	else {
		etat_f = CONSTRAINED;
	}
}

void Fourmiliere::maj_generator(Ensemble_food& ensemble_food) {
	ensemble_fourmis[0]->consommation(nbT);
	create_fourmi();
	ensemble_fourmis[0]->deplacement_generator(carre);
}

void Fourmiliere::create_fourmi() {
	random_device rd;
	double total_food = ensemble_fourmis[0]->get_total_food();
	double p(min(1.0, total_food * birth_rate));
	bernoulli_distribution b(p);
	default_random_engine eng(rd());
	if(b(eng)) {
		if(etat_f == FREE) {
			create_fourmi_free();
		}
		if(etat_f == CONSTRAINED) {
			create_fourmi_constrained();
			
		}
	}
}

void Fourmiliere::create_fourmi_free() {
	enum fourmi{C, D, P};
	double proba_C(0), proba_D(0);
	if(nbT-1 ==0) {
		proba_C=0;
	} else {
		proba_C = (double)nbC/(nbT-1);
		proba_D = (double)nbD/(nbT-1);
	}
	if(proba_C < prop_free_collector) {
		Carre carre_collector{sizeC, {0,0}};
		if(recherche_espace_libre(carre_collector)) {
			unsigned int age(0);
			ajouter_fourmis(new Collector(carre_collector, age), C);
			++nbC; ++nbT;
		return;
		}
		
	} else if(proba_D < prop_free_defensor) {
		Carre carre_defensor{sizeD, {0,0}};
		if(recherche_espace_libre(carre_defensor)) {
			unsigned int age(0);
			ajouter_fourmis(new Defensor(carre_defensor, age), D);
			++nbD; ++nbT;
		return;
		}
		
	} else {
		Carre carre_predator{sizeP, {0,0}};
		if(recherche_espace_libre(carre_predator)) {
			unsigned int age(0);
			ajouter_fourmis(new Predator(carre_predator, age), P);
			++nbP; ++nbT;
		return;
		}
	}
}

void Fourmiliere::create_fourmi_constrained() {
	enum fourmi{C, D, P};
	double proba_C(0), proba_D(0);
	if(nbT-1 ==0) {
		proba_C=0;
	} else {
		proba_C = (double)nbC/(nbT-1);
		proba_D = (double)nbD/(nbT-1);
	}
	cout << proba_C << " " << proba_D << endl;
	if(proba_C < prop_constrained_collector) { 
		Carre carre_collector{sizeC, {0,0}};
		if(recherche_espace_libre(carre_collector)) {
			unsigned int age(0);
			ajouter_fourmis(new Collector(carre_collector, age), C);
			++nbC; ++nbT;
			return;
		}	
	} else if(proba_D < prop_constrained_defensor) {
		Carre carre_defensor{sizeD, {0,0}};
		if(recherche_espace_libre(carre_defensor)) {
			unsigned int age(0);
			ajouter_fourmis(new Defensor(carre_defensor, age), D);
				++nbD; ++nbT;
				return;
			}
	} else {
		Carre carre_predator{sizeP, {0,0}};
		if(recherche_espace_libre(carre_predator)) {
			unsigned int age(0);
			ajouter_fourmis(new Predator(carre_predator, age), P);
			++nbP; ++nbT;
			return;
		}	
	}
}
	
bool Fourmiliere::recherche_espace_libre(Carre& carre_fourmi) {
	if(find_place_in_carre(carre, carre_fourmi)) {
		initialise_carre_centre(carre_fourmi);
		return true;
	} 
	return false;
}	

void Fourmiliere::action_autres_fourmis( Ensemble_food& ensemble_food) {
	Carre carre_fourmi = ensemble_fourmis[0]->get_carre();
	double total_food = ensemble_fourmis[0]->get_total_food();
	if(ensemble_fourmis[0]->get_end_of_klan()==false) {
		 for(size_t i(1); i < nbC+1; ++i) {
			cout << "COLLECTOR " << i << endl;
			if(ensemble_fourmis[i]->get_age() > 0) {
				ensemble_fourmis[i]->deplacement_collector(carre, carre_fourmi, ensemble_food, total_food);
			}
		}
		for(size_t i(nbC+1); i < nbC+nbD+1; ++i) {
			cout << "DEFENSOR  " << i << endl;
			if(ensemble_fourmis[i]->get_age() > 0) {
				ensemble_fourmis[i]->deplacement_defensor(carre);
			}
		}
	}
	for(size_t i(1); i < ensemble_fourmis.size();++i) {
		ensemble_fourmis[i]->incrementer_age();
	}
	ensemble_fourmis[0]->set_total_food(total_food);
}
	
void Fourmiliere::fourmi_kill(Fourmiliere& f, unsigned int etat_kill) {
	for(size_t i(1); i < nbC+1; ++i) {
		for(size_t j(f.nbC+1); j < f.ensemble_fourmis.size(); ++j) {
			Carre carre_f = f.ensemble_fourmis[j]->get_carre();
			ensemble_fourmis[i]->get_kill(carre_f, etat_kill);
		}
	}
	for(size_t i(nbC + nbD + 1); i < ensemble_fourmis.size(); ++i) {
		for(size_t j(f.nbC + f.nbD + 1); j < f.ensemble_fourmis.size(); ++j) {
			Carre carre_f = f.ensemble_fourmis[j]->get_carre();
			ensemble_fourmis[i]->get_kill(carre_f, etat_kill);
		}
	}

}

void Fourmiliere::intrusion_fourmi(Fourmiliere& f, vector<Carre>& fourmis_infiltres) {
	for(size_t i(0); i < f.ensemble_fourmis.size(); ++i) {
		Carre carre_f = f.ensemble_fourmis[i]->get_carre();
		if(test_superposition_2_carres_non_centre_centre(carre_f, carre)) {
			fourmis_infiltres.push_back(carre_f);
		}
	}	
}

void Fourmiliere::closest_fourmi(Fourmiliere& f, vector<Carre>& closest_fourmis) {
	for(size_t i(1); i < f.nbC+1; ++i) {
		Carre carre_f = f.ensemble_fourmis[i]->get_carre();
		closest_fourmis.push_back(carre_f);
	}
	for(size_t i(f.nbC+f.nbD+1); i < f.ensemble_fourmis.size(); ++i) {
		Carre carre_f = f.ensemble_fourmis[i]->get_carre();
		closest_fourmis.push_back(carre_f);
	}
}

void Fourmiliere::predator_in_house() {
	for(size_t i(nbC + nbD + 1); i < ensemble_fourmis.size(); ++i) {
		if(ensemble_fourmis[i]->fourmis_in_house(carre)) {
			ensemble_fourmis[i]->deplacement_predator_in_house(carre);
		}
	}
}

void Fourmiliere::deplacement_predator(vector<Carre> fourmis) {
	for(size_t i(nbC + nbD + 1); i < ensemble_fourmis.size(); ++i) {
		ensemble_fourmis[i]->deplacement_predator(fourmis);
	}
}

void Fourmiliere::destruction_fourmis(Ensemble_food& ensemble_food) {
	for(size_t i(1);  i < ensemble_fourmis.size(); ++i) {
		if(ensemble_fourmis[i]->get_age() >= bug_life or 
		   ensemble_fourmis[i]->get_end_of_life() == true) {
			ensemble_fourmis[i]->destruction_fourmi(ensemble_food, nbC, nbD, nbP);
			ensemble_fourmis.erase(ensemble_fourmis.begin()+i); //supprime pas comme il faut
			--i;
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
	unsigned int side, total_food;
	int x, y , xg, yg;
	static unsigned int countF(0), countC(0), countD(0), countP(0), count_fourmis(0),
	nbC, nbD, nbP, color(1);
	if(etat_f==FRMIL) {
		data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
		unsigned int nbT= 1+nbC+nbD+nbP;
		Carre carre{side, {x, y}};
		unsigned int sizeF= sqrt(4*(sizeG*sizeG + sizeC*sizeC*nbC + sizeD*sizeD*nbD + 
		sizeP*sizeP*nbP));
		Fourmiliere fourmiliere(carre, nbC, nbD, nbP, nbT, sizeF, color);
		if(color == 6) {
			color = 0;
		}
		++color;
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
				color = 1;
				return true;
			}
		}
		Carre carre_generator{sizeG, {xg, yg}};
		fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
		if(fourmiliere.test_fourmis(countF, count_fourmis)) {
			count_fourmis=0; 
			countF=0; 
			color = 1;
			return true;
		}
		ensemble_fourmilieres.push_back(std::move(fourmiliere));
		++count_fourmis;
		countC=0; countD=0; countP=0;
		if(nbC!=0) {
			etat_f=COLLECT;
			return false;
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
			++countF;
			if(ensemble_fourmilieres.size()==total) {
				color = 1;
				countF = 0; 
				etat = 0; 
				return false;
			}
		}
		return false;
	} 
	if(decodage_line_ensemble_fourmis(line, &ensemble_fourmilieres[countF], count_fourmis, 
	countF, etat_f, countC, countD, countP, nbC, nbD, nbP, color)) {
		return true;
	}
	if(ensemble_fourmilieres.size()==total and countC==nbC and countD==nbD
	  and countP==nbP) {
		countF = 0; 
		count_fourmis=0; 
		color = 1;
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
									unsigned int& nbP, unsigned int& color) {
	Carre carre{0, {0, 0}}; Collector collector(carre, 0);
	Defensor defensor(carre, 0); Predator predator(carre, 0);
	enum fourmi{C, D, P};
	switch(etat_f) {
		case 1 :
			decodage_line_fourmis(line, etat_f, collector, defensor, predator);
			(*fourmiliere).ajouter_fourmis(new Collector(collector));
			if((*fourmiliere).test_fourmis(countF, count_fourmis)) {
				etat_f = 0 ; 
				countF=0; 
				count_fourmis=0; 
				color = 1;
				return true;
			}
			++count_fourmis; ++countC;
			if(countC==nbC  and nbD == 0 and nbP == 0) { 
				etat_f= 0; 
				count_fourmis=0; 
				++countF; 
				break;
			} else if(countC==nbC and nbD==0) {
				etat_f = 3;
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
				countF=0; 
				count_fourmis=0;
				color = 1; 
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
				color = 1;
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
