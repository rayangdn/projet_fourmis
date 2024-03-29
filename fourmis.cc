//fourmi.cc
//Rayan Gauderon membre1: 60%
//Maxime Luyet membre 2: 40%

#include <iostream>
#include <random>
#include <cmath>

#include "fourmis.h"

using namespace std;
 
Fourmi::Fourmi(Carre carre, unsigned int age)
 : carre(carre), age(age), end_of_life(false) {}

Generator::Generator(Carre carre, unsigned int total_food) 
: Fourmi(carre, 0), total_food(total_food), end_of_klan(false) {}

Collector::Collector(Carre carre, unsigned int age)
: Fourmi(carre, age), etat_c(EMPTY) {}

Defensor::Defensor(Carre carre, unsigned int age) : Fourmi(carre, age) {}

Predator::Predator(Carre carre, unsigned int age) : Fourmi(carre, age) {}

unsigned int Fourmi::get_age() const {
	return age;
}

Carre Fourmi::get_carre() const {
	return carre;
}

bool Fourmi::get_end_of_life() const {
	return end_of_life;
}

void Fourmi::initialise_fourmi() {
	initialise_carre_centre(carre);
}

bool Fourmi::fourmis_in_house(const Carre& carre_fourmiliere) { 
	if(((carre.point.x-carre.longeur/2) <= (carre_fourmiliere.point.x)) or
		((carre.point.y-carre.longeur/2) <= (carre_fourmiliere.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= 
		(carre_fourmiliere.point.x + carre_fourmiliere.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= 
		(carre_fourmiliere.point.y +carre_fourmiliere.longeur))) {
			return true;
		}
	return false;
}

void Fourmi::ecriture_frmi(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y) 
	<< " " << to_string(age) << "\n";
}

void Fourmi::incrementer_age() {
	++age;
}	

void Fourmi::deplacement_droite_haut() {
	supprimer_carre_centre(carre);
	carre.point.x += 1;
	carre.point.y += 1;
	if(test_superposition_sans_coord(carre)) {
		
		carre.point.x -= 1;
		carre.point.y -= 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_droite_bas() {
	supprimer_carre_centre(carre);
	carre.point.x += 1;
	carre.point.y -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 1;
		carre.point.y += 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_gauche_haut() {
	supprimer_carre_centre(carre);
	carre.point.x -= 1;
	carre.point.y += 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 1;
		carre.point.y -= 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_gauche_bas() {
	supprimer_carre_centre(carre);
	carre.point.x -= 1;
	carre.point.y -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 1;
		carre.point.y += 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_bas() {
	supprimer_carre_centre(carre);
	carre.point.y -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.y += 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_gauche() {
	supprimer_carre_centre(carre);
	carre.point.x -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_droite() {
	supprimer_carre_centre(carre);
	carre.point.x += 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 1;
	}
	initialise_carre_centre(carre);
}

void Fourmi::deplacement_haut() {
	supprimer_carre_centre(carre);
	carre.point.y += 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.y -= 1;
	}
	initialise_carre_centre(carre);
}
void Fourmi::get_kill(const Carre& carre_fourmi, unsigned int etat_kill) {
	int vx = carre_fourmi.point.x - carre.point.x;
	int vy = carre_fourmi.point.y - carre.point.y;
	if(etat_kill==0) {
		if(abs(vx) <= 3 and abs(vy) <= 3) {
			end_of_life=true;
		}
	} else if(etat_kill==1) {
		if(carre.longeur==3) {
			if(abs(vx) <= 2 and abs(vy) <= 2) {
				end_of_life=true;
			}
		} else if(carre.longeur==1) {
			if(abs(vx) <= 1 and abs(vy) <= 1) {
				end_of_life=true;
			}
		}
	}
}
double Generator::get_total_food() const {
	return total_food;
}

void Generator::set_total_food(double total_f) {
	total_food = total_f;
}

bool Generator::get_end_of_klan() const {
	return end_of_klan;
}

bool Generator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_G()) {
		return true;
	}
	if(fourmis_in_house_G(countF, carre_fourmiliere)) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Generator::superposition_fourmi_G() {
	unsigned int x, y;
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::generator_overlap(carre.point.x, carre.point.y, x, y);
		return true;
	}
	return false;
}

bool Generator::fourmis_in_house_G(unsigned int countF, const Carre& carre_fourmiliere) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::generator_not_within_home(carre.point.x, carre.point.y,
		countF);
		return true;
	}
	return false;
}

bool Generator::generator_good_position(const Carre& carre_f) {
	if((carre.point.x== carre_f.point.x + carre_f.longeur/2) and
	   (carre.point.y == carre_f.point.y + carre_f.longeur/22)) {
		   return true;
	}
	return false;
}

void Generator::ecriture_frmi(ofstream& fichier) const {
	fichier << " " << to_string(carre.point.x) << " " << to_string(carre.point.y) << 
	" " << to_string((int)total_food) << " ";
	
}

void Generator::draw_fourmis(unsigned int couleur) {
	unsigned int style(UNIFORME);
	draw_carre(carre, style, couleur);
}

void Generator::consommation(unsigned int nbT) {
	total_food -= nbT*food_rate;
	if(total_food <= 0) {
		end_of_klan = true;
	}
}

void Generator::deplacement_generator(const Carre& carre_f) {
	if(fourmis_in_house(carre_f)) {
		end_of_klan = true;
		return;
	}				
	if(generator_good_position(carre_f) == false){
		
		if(carre.point.x < carre_f.point.x + carre_f.longeur/2 and 
		   carre.point.y < carre_f.point.y + carre_f.longeur/2) {
					deplacement_droite_haut();
		} else if(carre.point.x < carre_f.point.x + carre_f.longeur/2 and 
		          carre.point.y == carre_f.point.y + carre_f.longeur/2) {
					deplacement_droite();
		} else if(carre.point.x < carre_f.point.x + carre_f.longeur/2 and 
				  carre.point.y > carre_f.point.y + carre_f.longeur/2) {
					deplacement_droite_bas();
		} else if(carre.point.x > carre_f.point.x + carre_f.longeur/2 and
		          carre.point.y < carre_f.point.y + carre_f.longeur/2) {
					deplacement_gauche_haut();
		} else if(carre.point.x > carre_f.point.x + carre_f.longeur/2 and
		          carre.point.y == carre_f.point.y + carre_f.longeur/2) {
					 deplacement_gauche();
		} else if(carre.point.x > carre_f.point.x + carre_f.longeur/2 and
		          carre.point.y > carre_f.point.y + carre_f.longeur/2) {
					  deplacement_gauche_bas();
		} else if(carre.point.x == carre_f.point.x + carre_f.longeur/2 and
				  carre.point.y < carre_f.point.y + carre_f.longeur/2) {
					  deplacement_haut();
		} else if(carre.point.x == carre_f.point.x + carre_f.longeur/2 and
				  carre.point.y > carre_f.point.y + carre_f.longeur/2) {
					  deplacement_bas();
		}
	}
}

void Generator::destruction_fourmi(Ensemble_food& ensemble_food, unsigned int& nbC, 
								   unsigned int& nbD, unsigned int& nbP) {
	nbC=0; nbD=0; nbP=0;
	supprimer_carre_centre(carre);
}

void Collector::initialise_collect(const Carre& autre_carre, unsigned int autre_age,
								   string have_food) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
	if(have_food == "true") {
		etat_c = LOADED;
		
	} else { 
		etat_c = EMPTY;
	}
}

bool Collector::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_C()) {
		return true;
	}
	initialise_fourmi();
	return false;

}

bool Collector::superposition_fourmi_C() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::collector_overlap( carre.point.x, carre.point.y, x, y);
		return true;
	}
	return false;
}

void Collector::ecriture_frmi(ofstream& fichier) const {
	fichier << "\t" << to_string(carre.point.x) << " " << to_string(carre.point.y) << 
	" " << to_string(age) << " ";
	string have_food_string;
	if(etat_c == LOADED) {
		have_food_string="true\n";
	} else {
		have_food_string="false\n";
	}
	fichier << have_food_string;
}

void Collector::draw_fourmis(unsigned int couleur) {
	unsigned int style(DIAGONALE);
	draw_carre(carre, style, couleur);
	if(etat_c==LOADED) {
		unsigned int style(LOSANGE);
		unsigned int couleur(WHITE);
		Carre carre_food{1, {carre.point.x, carre.point.y}};
		draw_carre(carre_food, style, couleur);
	}
}

void Collector::deplacement_collector(const Carre& carre_f, Carre& carre_generator,
								   Ensemble_food& ensemble_food, double& total_food) {
	if(etat_c==EMPTY) {
		 deplacement_collector_empty(carre_f, ensemble_food);
	} else if(etat_c==LOADED) {
		deplacement_collector_loaded(carre_f, carre_generator, total_food);
	}
	
}


void Collector::deplacement_collector_loaded(const Carre& carre_f, Carre carre_generator,
											 double& total_food) {
	int vx = carre_generator.point.x-carre.point.x;
	int vy = carre_generator.point.y - carre.point.y;
	if(abs(vx) == abs(vy) or abs(vy)+1 == abs(vx) or abs(vy) == abs(vx)+1 or 
	   abs(vy)-1 == abs(vx) or abs(vy) == abs(vx)-1) {
		if(deplacement_chemin_1_loaded(carre_f, vx, vy)) {
			etat_c = EMPTY;
			total_food += val_food;
		}
	} else {
		if(deplacement_chemin_2_loaded(carre_f,carre_generator, vx, vy)) {
			etat_c = EMPTY;
			total_food += val_food;
		}
	}
}

void Collector::deplacement_collector_empty(const Carre& carre_f, Ensemble_food& ensemble_food) {
	int i(test_diago_proximities(ensemble_food));
	if( i == -1) {
		if(test_superposition_2_carres_non_centre_centre(carre, carre_f)) {
			deplacement_collector_out(carre_f);
		}
		return;
	}
	int vx = ensemble_food[i].get_carre().point.x - carre.point.x;
	int vy = ensemble_food[i].get_carre().point.y - carre.point.y;
	if(abs(vx) == abs(vy) or abs(vy)+1 == abs(vx) or abs(vy) == abs(vx)+1 or 
	   abs(vy)-1 == abs(vx) or abs(vy) == abs(vx)-1) {
		if(deplacement_chemin_1_empty(ensemble_food[i].get_carre(), vx, vy)) {
			etat_c = LOADED;
			ensemble_food.erase(ensemble_food.begin()+i);
			
		}
	} else {
		if(deplacement_chemin_2_empty(ensemble_food[i].get_carre(), vx, vy)) {
			etat_c = LOADED;
			ensemble_food.erase(ensemble_food.begin()+i);
		}
	}	
} 

void Collector::deplacement_collector_out(const Carre& carre_f) {
	int x_b1 =  (carre.point.x-carre_f.point.x-1);
	int x_b2 =  (carre_f.point.x+carre_f.longeur-1-carre.point.x);
	int y_b1 =  (carre.point.y-carre_f.point.y-1);
	int y_b2 =  (carre_f.point.y+carre_f.longeur-1-carre.point.y);
	int i(0);
	if(test_deplacement_bordure(carre, i)) {
		return;
	}
	if(x_b1 <= x_b2 and y_b1 <= y_b2) {
		deplacement_gauche_bas();
	} else if(x_b1 > x_b2 and y_b1 <= y_b2) {
		deplacement_droite_bas();
	} else if(x_b1 <= x_b2 and y_b1 > y_b2) {
		deplacement_gauche_haut();
	} else if(x_b1 > x_b2 and y_b1 > y_b2) {
		deplacement_droite_haut();
	}
}

int Collector::test_diago_proximities(const Ensemble_food& ensemble_food) {
	int index(0);
	if(ensemble_food.size() == 0) {
		index = -1;
		return index;
	}
	vector<unsigned int> proximities;
	for(size_t i(0); i < ensemble_food.size(); ++i) {
		unsigned int prox(0);
		if(test_diago(carre, ensemble_food[i].get_carre())) {
			int vx = ensemble_food[i].get_carre().point.x - carre.point.x;
			int vy = ensemble_food[i].get_carre().point.y - carre.point.y;
			prox = max(abs(vx), abs(vy));
		}
		proximities.push_back(prox);
	}
	
	for(size_t i(0); i < proximities.size(); ++i) {
		if(proximities[i]==0) {
			index = -1;
		} else {
			index = 0;
			break;
		}
	}
	if(index==-1) {
		return index;
	}
	
	for(size_t i(0); i < proximities.size(); ++i) {
		if((proximities[i] < proximities[index] and proximities[i] != 0) or proximities[index] ==0) {
			index = i;
		}
	}
	return index;
}

bool Collector::deplacement_chemin_1_empty(const Carre& carre_food, int vx, int vy) {
	supprimer_carre_centre(carre_food);
	if(vx < 0 and vy < 0) {
		deplacement_gauche_bas();
	} else if(vx > 0 and vy > 0) {
		deplacement_droite_haut();
	} else if(vx < 0 and vy > 0) {
		 deplacement_gauche_haut();
	} else if(vx > 0 and vy < 0) {
		deplacement_droite_bas();
	}
	
	if(test_superposition_2_carres_centre(carre, carre_food)) {
		supprimer_carre_centre(carre_food);
		return true;
	}
	initialise_carre_centre(carre_food);
	return false;
}

bool Collector::deplacement_chemin_2_empty(const Carre& carre_food, int vx, int vy) {
	bool bordure(false);
	int saut1((vx+vy)/2);
	int saut2((vx-vy)/2);
	
	supprimer_carre_centre(carre_food);
	unsigned int chemin(best_chemin(saut1, saut2, bordure));
	cout << "SAUTS " << saut1 << " " << saut2 << endl;
	cout << "BORDURE " << bordure << endl;
	if(bordure==false) {
		deplacement_no_bordure(chemin, saut1, saut2);
	} else {
		deplacement_bordure(chemin, saut1, saut2, vx, vy);
	}
	if(test_superposition_2_carres_centre(carre, carre_food)) {
		supprimer_carre_centre(carre_food);
		return true;
	}
	initialise_carre_centre(carre_food);
	return false;
}

bool Collector::deplacement_chemin_1_loaded(const Carre& carre_f, int vx, int vy) {
	if(vx < 0 and vy < 0) {
		deplacement_gauche_bas();
	} else if(vx > 0 and vy > 0) {
		deplacement_droite_haut();
	} else if(vx < 0 and vy > 0) {
		 deplacement_gauche_haut();
	} else if(vx > 0 and vy < 0) {
		deplacement_droite_bas();
	}
	if(test_superposition_2_carres_non_centre_centre(carre, carre_f)) {
		return true;
	}
	return false;
}

bool Collector::deplacement_chemin_2_loaded(const Carre& carre_f, Carre carre_generator,
											int vx, int vy) {
	bool bordure(false);
	int saut1((vx+vy)/2);
	int saut2((vx-vy)/2);
	supprimer_carre_centre(carre_generator);
	unsigned int chemin(best_chemin(saut1, saut2, bordure));
	initialise_carre_centre(carre_generator);
	cout << "SAUTS " << saut1 << " " << saut2 << endl;
	cout << "BORDURE " << bordure << endl;
	
	if(bordure==false) {
		deplacement_no_bordure(chemin, saut1, saut2);
	} else {
		deplacement_bordure(chemin, saut1, saut2, vx, vy);
	}
	if(test_superposition_2_carres_non_centre_centre(carre, carre_f)) {
		return true;
	}
	return false;
}

void Collector::test_saut_bordure(int i, int& saut_bordure, int vx, int vy, int saut1,
								  int saut2) {
		 if(i==1) {
			if(vy > 0) {
				saut_bordure = saut2;
			} else {
				saut_bordure = saut1;
			}
		}
		if(i ==2) {
			if(vy < 0) {
				saut_bordure = saut2;
			} else {
				saut_bordure = saut1;
			}
		}
		if(i==3) {
			if(vx < 0) {
				saut_bordure = saut1;
			} else {
				saut_bordure = saut2;
			}
		}
		if(i==4) {
			if(vx > 0) {
				saut_bordure = saut1;
			} else {
				saut_bordure = saut2;
			}
		}
}

unsigned int Collector::best_chemin(int& saut1, int& saut2, bool& bordure) {
	supprimer_carre_centre(carre);
	Carre test = carre;
	unsigned int chemin(test_chemin(test, saut1, saut2, bordure));
	initialise_carre_centre(carre);
	return chemin;
}

void Collector::deplacement_no_bordure(int chemin, int saut1, int saut2) {
	cout << "CHEMIN" << chemin << endl;
	if(chemin==1) {
		if(saut1 > 0 and saut2 > 0) {
			deplacement_droite_haut();
		} else if(saut1 < 0 and saut2 < 0) {
			deplacement_gauche_haut();
		} else if(saut1 < 0 and saut2 > 0) {
			deplacement_droite_bas();
		} else if(saut1 > 0 and saut2 < 0) {
			deplacement_droite_haut();
		}	
	} else if(chemin==2) {
		if(saut1 > 0 and saut2 > 0) {
			deplacement_droite_bas();
		} else if(saut1 < 0 and saut2 < 0) {
			deplacement_gauche_bas();
		} else if(saut1 < 0 and saut2 > 0) {
			deplacement_gauche_bas();
		} else if(saut1 > 0 and saut2 < 0) {
			deplacement_gauche_haut();
		}
	}
}

void Collector::deplacement_bordure(int chemin, int saut1, int saut2, int vx, int vy) {
	static int i(0);
	int saut_bordure(0);
	test_deplacement_bordure(carre, i);
	cout << "BORD " << i << endl;
	test_saut_bordure(i, saut_bordure, vx, vy , saut1, saut2);
	if(i==1) {
		deplacement_left_bordure(i, saut1, saut_bordure);	
	}
	if(i==2) {
		deplacement_right_bordure(i, saut1, saut_bordure);
	}
	if(i==3) {
		deplacement_bottom_bordure(i, saut1, saut_bordure);
	}
	if(i==4) {
		deplacement_top_bordure(i, saut1, saut_bordure);
	} else if(i==0) {
		deplacement_no_bordure(chemin, saut1, saut2);
	}
}

void Collector::deplacement_left_bordure(int& i, int saut1, int saut_bordure) {
	static int j(0);
	if(saut1 > 0) {
		if(j<abs(saut_bordure)) {
			deplacement_droite_haut();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_gauche_haut();
		}
	} else if(saut1 < 0) {
		if(j<abs(saut_bordure)) {
			deplacement_droite_bas();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_gauche_bas();
		}
	}
}

void Collector::deplacement_right_bordure(int& i, int saut1, int saut_bordure) {
	static int j(0);
	if(saut1 > 0) {
		if(j<abs(saut_bordure)) {
			deplacement_gauche_haut();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_droite_haut();
		}
	} else if(saut1 < 0) {
		if(j<abs(saut_bordure)) {
			deplacement_gauche_bas();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_droite_bas();
		}
	}
}

void Collector::deplacement_bottom_bordure(int& i, int saut1, int saut_bordure) {
	static int j(0);
	if(saut1 > 0) {
		if(j<abs(saut_bordure)) {
			deplacement_droite_haut();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_droite_bas();
		}
	} else if(saut1 < 0) {
		if(j<abs(saut_bordure)) {
			deplacement_gauche_haut();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_gauche_bas();
		}
	}
}

void Collector::deplacement_top_bordure(int& i, int saut1, int saut_bordure) {
	static int j(0);
	if(saut1 > 0) {
		if(j<abs(saut_bordure)) {
			deplacement_droite_bas();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_droite_haut();
		}
	} else if(saut1 < 0) {
		if(j<abs(saut_bordure)) {
			deplacement_gauche_bas();
			++j;
		} else {
			j=0;
			i=0;
			deplacement_gauche_haut();
		}
	}
}
	
void Collector::destruction_fourmi(Ensemble_food& ensemble_food, unsigned int& nbC, 
								   unsigned int& nbD, unsigned int& nbP) {
	--nbC;
	if(etat_c==LOADED) {
		Carre carre_food{1, {carre.point.x, carre.point.y}};
		Food food(carre_food);
		ensemble_food.push_back(food);
		initialise_carre_centre(carre_food);
	}
	supprimer_carre_centre(carre);
}
	
void Defensor::initialise_defens(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

bool Defensor::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_D()) {
		return true;
	}
	if(fourmis_in_house_D(countF, carre_fourmiliere)) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Defensor::superposition_fourmi_D() {
	unsigned int x(0), y(0);
	if(test_superposition_avec_coord(carre, x, y)) {
		cout << message::defensor_overlap( carre.point.x, carre.point.y, x, y );
		return true;
	}
	return false;
}

bool Defensor::fourmis_in_house_D(unsigned int countF, const Carre& carre_fourmiliere) {
	if(fourmis_in_house(carre_fourmiliere)) {
		cout << message::defensor_not_within_home(carre.point.x, carre.point.y,
		countF);
		return true;
	}
	return false;
}

void Defensor::draw_fourmis(unsigned int  couleur) {
	unsigned int style(GRILLE);
	draw_carre(carre, style, couleur);
}

void Defensor::deplacement_defensor(const Carre& carre_f) {
	if(fourmis_in_house(carre_f)) {
		end_of_life=true;
		return;
	}
	int x_b1 =  (carre.point.x-carre.longeur/2-carre_f.point.x-1);
	int x_b2 =  (carre_f.point.x+carre_f.longeur-2-carre.point.x-carre.longeur/2);
	int y_b1 =  (carre.point.y-carre.longeur/2-carre_f.point.y-1);
	int y_b2 =  (carre_f.point.y+carre_f.longeur-2-carre.point.y-carre.longeur/2);
	if(x_b1 == 0 or x_b2 == 0 or y_b1 == 0 or y_b2 == 0) {
		return;
	}
	if( x_b1 <= x_b2) {
		if( y_b1 <= y_b2) {
			if ( x_b1 <= y_b1) {
				deplacement_gauche();
			} else {
				deplacement_haut();
			}
		} 
	}
	if( x_b2 < x_b1) {
		if( y_b1 <= y_b2) {
			if ( x_b2 <= y_b1) {
				deplacement_droite();
			} else {
				deplacement_bas();
			}
		} 
	}
	if( x_b1 <= x_b2) {
		if( y_b2 < y_b1) {
			if ( x_b1 <= y_b2) {
				deplacement_gauche();
			} else {
				deplacement_haut();
			}
		} 
	}
	if( x_b2 < x_b1) {
		if( y_b2 < y_b1) {
			if ( x_b2 <= y_b2) {
				deplacement_droite();
			} else {
				deplacement_haut();
			}
		} 
	}
}

void Defensor::destruction_fourmi(Ensemble_food& ensemble_food, unsigned int& nbC, 
								  unsigned int& nbD, unsigned int& nbP) {
	--nbD;
	supprimer_carre_centre(carre);
}

void Predator::initialise_predat(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
}

bool Predator::test_chaque_fourmi(unsigned int countF, const Carre& carre_fourmiliere) {
	if(test_validation_carre_centre(carre)) {
		return true;
	}
	if(superposition_fourmi_P()) {
		return true;
	}
	initialise_fourmi();
	return false;
}

bool Predator::superposition_fourmi_P() {
	if(test_superposition_sans_coord(carre)) {
		cout << message::predator_overlap(carre.point.x, carre.point.y);
		return true;
	}
	return false;
}

void Predator::draw_fourmis(unsigned int couleur) {
	unsigned int style(UNIFORME);
	draw_carre(carre, style, couleur);
}

void Predator::deplacement_predator(vector<Carre> fourmis_infiltres) {
	unsigned int i(test_proximities(fourmis_infiltres));
	int vx = fourmis_infiltres[i].point.x - carre.point.x;
	int vy = fourmis_infiltres[i].point.y - carre.point.y;
	supprimer_carre_centre(fourmis_infiltres[i]);
	if(vx > 0 and vy > 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_haut_droite_2();
		} else {
			deplacement_haut_droite_1();
		}
	} else if (vx <= 0 and vy <= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_bas_gauche_2();
		} else {
			deplacement_bas_gauche_1();
		}
	} else if (vx <= 0 and vy >= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_haut_gauche_1();
		} else {
			deplacement_haut_gauche_2();
		}
	} else if(vx >= 0 and vy <= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_bas_droite_1();
		} else {
			deplacement_bas_droite_2();
		}
	}
	initialise_carre_centre(fourmis_infiltres[i]);
}

void Predator::deplacement_predator_in_house(const Carre& carre_f) {
	int vx = carre_f.point.x +carre_f.longeur/2- carre.point.x;
	int vy = carre_f.point.y +carre_f.longeur/2- carre.point.y;
	if(vx > 0 and vy > 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_haut_droite_2();
		} else {
			deplacement_haut_droite_1();
		}
	} else if (vx <= 0 and vy <= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_bas_gauche_2();
		} else {
			deplacement_bas_gauche_1();
		}
	} else if (vx <= 0 and vy >= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_haut_gauche_1();
		} else {
			deplacement_haut_gauche_2();
		}
	} else if(vx >= 0 and vy <= 0) {
		if(abs(vx) > abs(vy)) {
			deplacement_bas_droite_1();
		} else {
			deplacement_bas_droite_2();
		}
	}
}

unsigned int Predator::test_proximities(vector<Carre> fourmis_infiltres) {
	vector<double> proximities;
	double prox(0);
	for(size_t i(0); i < fourmis_infiltres.size(); ++i) {
		int vx = fourmis_infiltres[i].point.x - carre.point.x;
		int vy = fourmis_infiltres[i].point.y - carre.point.y;
		prox = sqrt(vx*vx + vy*vy);
		proximities.push_back(prox);
	}
	unsigned int index(0);
	for(size_t i(0); i < proximities.size(); ++i) {
		if(proximities[i] < proximities[index]) {
			index = i;
		}
	}
	return index;
}

void Predator::deplacement_haut_gauche_1() {
	supprimer_carre_centre(carre);
	carre.point.x -= 2;
	carre.point.y += 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 2;
		carre.point.y -= 1;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_haut_gauche_2() {
	supprimer_carre_centre(carre);
	carre.point.x -= 1;
	carre.point.y += 2;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 1;
		carre.point.y -= 2;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_haut_droite_1() {
	supprimer_carre_centre(carre);
	carre.point.x += 1;
	carre.point.y += 2;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 1;
		carre.point.y -= 2;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_haut_droite_2() {
	supprimer_carre_centre(carre);
	carre.point.x += 2;
	carre.point.y += 1 ;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 2;
		carre.point.y -= 1;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_bas_droite_1() {
	supprimer_carre_centre(carre);
	carre.point.x += 2;
	carre.point.y -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 2;
		carre.point.y += 1;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_bas_droite_2() {
	supprimer_carre_centre(carre);
	carre.point.x += 1;
	carre.point.y -= 2;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x -= 1;
		carre.point.y += 2;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_bas_gauche_1() {
	supprimer_carre_centre(carre);
	carre.point.x -= 1;
	carre.point.y -= 2;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 1;
		carre.point.y += 2;
	}
	initialise_carre_centre(carre);
}

void Predator::deplacement_bas_gauche_2() {
	supprimer_carre_centre(carre);
	carre.point.x -= 2;
	carre.point.y -= 1;
	if(test_superposition_sans_coord(carre)) {
		carre.point.x += 2;
		carre.point.y += 1;
	}
	initialise_carre_centre(carre);
}

void Predator::destruction_fourmi(Ensemble_food& ensemble_food, unsigned int& nbC, 
								  unsigned int& nbD, unsigned int& nbP) {
	--nbP;
	supprimer_carre_centre(carre);
}

void decodage_line_fourmis(string line, unsigned int etat, Collector& collector,
                           Defensor& defensor, Predator& predator) {
	istringstream data(line);
	int x, y;
	unsigned int age;
	string have_food;
	if(etat==1) {
		data >> x >> y >> age >> have_food;
		Carre carre{sizeC, {x, y}};
		collector.initialise_collect(carre, age, have_food);
		return;
	}
	
	if(etat==2) {
		data >> x >> y >> age;
		Carre carre{sizeD, {x, y}};
		defensor.initialise_defens(carre, age);
		return;
	}
	if(etat==3) {
		data >> x >> y >> age;
		Carre carre{sizeP, {x, y}};
		predator.initialise_predat(carre, age);
		return;
	}
}
