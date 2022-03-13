#include <iostream>
#include <array>
#include <vector>

#include "Code_source/constantes.h"
#include  "Code_source/error_squarecell.h"
//CLASSE OU STRUCTURE???
using namespace std;
enum {VIDE, CARRE};

typedef array<array<unsigned int, 10> ,10> Grille; // remplacer 10 par g_max après
typedef vector<vector<unsigned int>> Carre;
typedef vector<vector<bool>> Test;
struct Point {
	unsigned int x;
	unsigned int y;
};


/*struct Squarcell{
	Grille grille;
	Carre carre;
	Point point;
};*/

void initalise(Grille& grille);
//void initialise0(Test& test);
void affiche(Test test);

void test_validation_carre(Carre carre, Grille& grille, Point point,Test& test);

void test_superposition(Carre carre, Carre carre1, Grille grille, Point point, Point point1, Test test); 
int main() {
	//Squarcell squarcell;
	Grille grille;
	Carre carre(4, vector<unsigned int> (4));
	Carre carre1(3, vector<unsigned int> (3));
	Point point{1,1};
	Point point1{4,4}; //carre, carre1, point, point1 à changer pour faire des tests
	Test test(10, vector<bool>(10));
	initalise(grille);
	//initialise0(test); besoin d'initaliser ou par défaut à false??
	
	test_validation_carre(carre, grille, point, test);
	test_validation_carre(carre1, grille, point1, test);
	test_superposition(carre,carre1, grille, point, point1, test);
	affiche(test);
	return 0;
}
void initalise(Grille& grille) {
	for(auto& ligne : grille) {
		for(auto& kase : ligne) {
			kase = VIDE;
		}
	}
}
/*
void initialise0(Test& test) {
	for(size_t i(0); i < test.size(); ++i) {
		for(size_t j(0); j < test[i].size(); ++j) {
			test[i][j] = false;
			cout << test[i][j];
		}
	}
}*/
void test_validation_carre(Carre carre, Grille& grille, Point point, Test& test) {
	for(size_t i(0); i < grille.size(); ++i) {
		for(size_t j(0); j < grille[i].size(); ++j) {
			if( j == point.x and i == 9-point.y) {
				for(size_t k(0); k < carre.size(); ++k) {
					for(size_t l(0); l < carre[k].size(); ++l) {
						if ( carre.size()+point.y > grille.size()-1
						 or carre[k].size()+point.x > grille[i].size()-1 ) {
							 cout << "No succes square";
							 exit (0);
						 } else {
							//grille[10-point.y-carre.size()+k][point.x+l] = CARRE; // utile pour l'affichage uniquement!!, plus besoin après
							test[10-point.y-carre.size()+k][point.x+l] = true;
						}
					}
				}
			}
		}
	}
}
void test_superposition(Carre carre, Carre carre1, Grille grille, Point point, Point point1, Test test) {
	unsigned int compteur(0);
	for(auto ligne : test) {
		for(auto kase : ligne) {
			if(kase == true){
				compteur += 1;
			}
		}
	}
	if ( compteur < carre.size()*carre.size() + carre1.size() *carre1.size()) {
		cout << "Superposition";
		//exit (0);
		cout << endl;
	}
	
}

void affiche(Test test) {
	for(auto ligne : test) {
		for(auto kase : ligne) {
			if( kase == false) {
				cout << "|___";
			} else if ( kase == true) {
				cout << "|_X_";
			}
		}
		cout << endl;
	}
}

	
