//fourmi.cc
//Rayan Gauderon membre1: 60%
//Maxime Luyet membre 2: 40%

#include <iostream>
#include <random>
#include <cmath>

#include "fourmis.h"

using namespace std;

static int vx_initial(0);

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
	<< "\n";
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

double Generator::get_total_food() const {
	return total_food;
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
	if((carre.point.x== carre_f.point.x + carre_f.longeur/2-1) and
	   (carre.point.y == carre_f.point.y + carre_f.longeur/2-1)) {
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

void Generator::deplacement_fourmi(const Carre& carre_f,  Ensemble_food& ensemble_food) {
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

void Collector::deplacement_fourmi(const Carre& carre_f, Ensemble_food& ensemble_food) {
	if(test_superposition_2_carres_non_centre_centre(carre, carre_f)) {
		deplacement_collector_out(carre_f);
		return;
	}
	if(etat_c==LOADED) {
		deplacement_collector_loaded(carre_f);
	}
	if(etat_c==EMPTY) {
		 deplacement_collector_empty(ensemble_food);
	}
}

void Collector::deplacement_collector_out(const Carre& carre_f) {
	int dist1 = carre.point.x+carre.longeur/2+1 - carre_f.point.x;
	int dist2 = carre_f.point.x+carre_f.longeur-1-carre.point.x-carre.longeur/2 ;
	int dist3 = carre.point.y+carre.longeur/2+1 - carre_f.point.y;
	int dist4 =  carre_f.point.y+carre_f.longeur-1-carre.point.y-carre.longeur/2;
	vector<int> proximities{dist1, dist2, dist3, dist4};
	unsigned int index = 0;
	for(size_t i(0); i < proximities.size(); ++i) {
		if(proximities[i] < proximities[index] and proximities[i] != 0) {
			index = i;
		}
	}
	if(index==0) {
		deplacement_gauche_bas();
	}
	if(index==1) {
		deplacement_droite_haut();
	}
	if(index==2) {
		deplacement_gauche_bas();
	}
	if(index==3) {
		deplacement_droite_haut();
	}
	
}

void Collector::deplacement_collector_loaded(const Carre& carre_f) {
	int vx(0); int vy(0);
		
	 vx = carre_f.point.x+sizeG/2 -carre.point.x;
	 vy = carre_f.point.y+sizeG/2 - carre.point.y;
	
	if(abs(vx) == abs(vy)) {
		if(deplacement_chemin_1_loaded(carre_f, vx, vy)) {
			etat_c = EMPTY;
			vx = 0;
			vy = 0;
		}
	} else {
		if(deplacement_chemin_2_loaded(carre_f, vx, vy)) {
			etat_c = EMPTY;
			vx = 0;
			vy = 0;
		}
	}
}

void Collector::deplacement_collector_empty(Ensemble_food& ensemble_food) {
	int i(test_diago_proximities(ensemble_food));
	if( i == -1) {
		return;
	}
	int vx = ensemble_food[i].get_carre().point.x - carre.point.x;
	int vy = ensemble_food[i].get_carre().point.y - carre.point.y;
	if(abs(vx) == abs(vy)) {
		if(deplacement_chemin_1_empty(ensemble_food[i].get_carre(), vx, vy)) {
			etat_c = LOADED;
			vx = 0;
			vy = 0;
			ensemble_food.erase(ensemble_food.begin()+i);
			
		}
	} else {
		if(deplacement_chemin_2_empty(ensemble_food[i].get_carre(), vx, vy)) {
			etat_c = LOADED;
			vx = 0;
			vy = 0;
			ensemble_food.erase(ensemble_food.begin()+i);
		}
	}	
} 

int Collector::test_diago_proximities(const Ensemble_food& ensemble_food) {
	if(ensemble_food.size() == 0) {
		return -1;
	}
	vector<unsigned int> proximities;
	for(size_t i(0); i < ensemble_food.size(); ++i) {
		unsigned int prox(0);
		if(test_diago(carre, ensemble_food[i].get_carre())) {
			int vx = ensemble_food[i].get_carre().point.x - carre.point.x;
			int vy = ensemble_food[i].get_carre().point.y - carre.point.y;
			prox = max(abs(vx), abs(vy));
			proximities.push_back(prox);
		} else {
			proximities.push_back(prox);
		}
	}
	unsigned int index = 0;
	for(size_t i(0); i < proximities.size(); ++i) {
		if(proximities[i] < proximities[index] and proximities[i] != 0) {
			index = i;
		}
	}
	proximities.clear();
	return index;
}

bool Collector::deplacement_chemin_1_empty(const Carre& carre_food, int vx, int vy) {
	cout << "EMPTY 1" << endl;
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
		vx_initial = 0;
		return true;
	}
	initialise_carre_centre(carre_food);
	return false;
}

bool Collector::deplacement_chemin_2_empty(const Carre& carre_food, int vx, int vy) {
	//sa saxe sur une diago au finale
	cout << "EMPTY 2 :" << endl;
	int x(0); int y(0);
	calcul_itineraire(vx, vy, x, y); //sans superposition
	
	if( vx_initial == 0) {
		vx_initial = vx;
	}
	supprimer_carre_centre(carre_food);
	if(vx_initial < 0) {
		if (x < 0) {
			deplacement_gauche_bas();
		} else if (x > 0) {
			deplacement_gauche_haut();
		}
	}
	if(vx_initial > 0) {
		if ( x < 0) {
			deplacement_droite_bas();
		} else if(x > 0) {
			deplacement_droite_haut();
		}
	}
	if(test_superposition_2_carres_centre(carre, carre_food)) {
		supprimer_carre_centre(carre_food);
		vx_initial = 0;
		return true;
	}
	initialise_carre_centre(carre_food);
	return false;
}

bool Collector::deplacement_chemin_1_loaded(const Carre& carre_f, int vx, int vy) {
	cout << "LOADED 1" << endl;
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
		vx_initial = 0;
		return true;
	}
	return false;
}

bool Collector::deplacement_chemin_2_loaded(const Carre& carre_f, int vx, int vy) {
	cout << "LOADED 2:" << endl;
	int x(0); int y(0);
	calcul_itineraire(vx, vy, x, y);
	if( vx_initial == 0) {
		vx_initial = vx;
	}
	if(vx_initial < 0) {
		if (x < 0) {
			deplacement_gauche_bas();
		} else if (x > 0) {
			deplacement_gauche_haut();
		}
	}
	if(vx_initial > 0) {
		if ( x < 0) {
			deplacement_droite_bas();
		} else if(x > 0) {
			deplacement_droite_haut();
		}
	}
	if(test_superposition_2_carres_non_centre_centre(carre, carre_f)) {
		vx_initial = 0;
		return true;
	}
	return false;
}

void Collector::calcul_itineraire(int vx, int vy, int& x, int& y) {
	for(int i(-g_max); i <= g_max; ++i) {
		for(int  j(-g_max); j <= g_max; ++j) {
			if( i+j== vx and i-j == vy) {
				x=i;
				y=-j; //ou -j selon superposition
			}
		}
	}
	//testet avec superposition
}

void Collector::destruction_fourmi(Ensemble_food& ensemble_food, unsigned int& nbC, 
								   unsigned int& nbD, unsigned int& nbP) {
	--nbC;
	if(etat_c==LOADED) {
		Carre carre_food{1, {carre.point.x, carre.point.y}};
		Food food(carre_food);
		ensemble_food.push_back(food);
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

void Defensor::deplacement_fourmi(const Carre& carre_f,  Ensemble_food& ensemble_food) {
	if(fourmis_in_house(carre_f)) {
		end_of_life=true;
		return;
	}
	//CALCUL DIST MINIM  A BORDURE ET VA AU PLUS PROCHE OKE??
	//SI COLLISION PAS DEE DEPLACEMENT OKE??
	int x_b1 =  (carre.point.x-carre.longeur/2-carre_f.point.x-1);//enlever la bordure
	int x_b2 =  (carre_f.point.x+carre_f.longeur-2-carre.point.x-carre.longeur/2);
	int y_b1 =  (carre.point.y-carre.longeur/2-carre_f.point.y-1);//enlever la bordure
	int y_b2 =  (carre_f.point.y+carre_f.longeur-2-carre.point.y-carre.longeur/2);
	if(x_b1 == 0 or x_b2 == 0 or y_b1 == 0 or y_b2 == 0) {
		return;
	}
	supprimer_carre_centre(carre);
	if( x_b1 <= x_b2) {
		if( y_b1 <= y_b2) {
			if ( x_b1 <= y_b1) {
				carre.point.x -= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.x+=1;
				} 
				initialise_carre_centre(carre);
			} else {
				carre.point.y-= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.y+=1;
				} 
				initialise_carre_centre(carre);
			}
		} 
	}
	if( x_b2 < x_b1) {
		if( y_b1 <= y_b2) {
			if ( x_b2 <= y_b1) {
				carre.point.x += 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.x-=1;
				} 
				initialise_carre_centre(carre);
			} else {
				carre.point.y-= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.y+=1;
				} 
				initialise_carre_centre(carre);
			}
		} 
	}
	if( x_b1 <= x_b2) {
		if( y_b2 < y_b1) {
			if ( x_b1 <= y_b2) {
				carre.point.x -= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.x+=1;
				} 
				initialise_carre_centre(carre);
			} else {
				carre.point.y+= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.y-=1;
				} 
				initialise_carre_centre(carre);
			}
		} 
	}
	if( x_b2 < x_b1) {
		if( y_b2 < y_b1) {
			if ( x_b2 <= y_b2) {
				carre.point.x += 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.x-=1;
				} 
				initialise_carre_centre(carre);
			} else {
				carre.point.y+= 1;
				if(test_superposition_sans_coord(carre)) {
					carre.point.y-=1;
				} 
				initialise_carre_centre(carre);
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
