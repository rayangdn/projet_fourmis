#include <iostream>
#include <array>
#include <vector>

#include "Code_source/constantes.h"
#include  "Code_source/error_squarecell.h"
//#include "carre.h"

using namespace std;
enum {VIDE, CARRE};
typedef array<array<unsigned int, 10> ,10> Grille;
typedef vector<vector<unsigned int>> Carre;
struct Point {
	unsigned int x;
	unsigned int y;
};
void initalise(Grille& grille);
//void initialise1(Point point, Grille& grille);
void affiche(Grille grille);

void test_validation_carre(Carre carre, Grille& grille, Point point); 
int main() {
	Grille grille;
	Carre carre(7, vector<unsigned int> (7));
	Point point{1,1};
	initalise(grille);
	//initialise1(point, grille);
	
	test_validation_carre(carre, grille, point);
	affiche(grille);

	

	return 0;
}
void initalise(Grille& grille) {
	for(auto& ligne : grille) {
		for(auto& kase : ligne) {
			kase = VIDE;
			
		}
	}
}

void test_validation_carre(Carre carre, Grille& grille, Point point) {
	for(size_t i(0); i < grille.size(); ++i) {
		for(size_t j(0); j < grille[i].size(); ++j) {
			if( j == point.x and i == 9-point.y) {
				for(size_t k(0); k < carre.size(); ++k) {
					for(size_t l(0); l < carre[k].size(); ++l) {
						if ( carre.size()+point.y > grille.size()
						 or carre[k].size()+point.x > grille[i].size() ) {
							 exit (0);
						 } else {
							grille[10-point.y-carre.size()+k][point.x+l] = CARRE;
						}
					}
				}
			}
		}
	}
}


void affiche(Grille grille) {
	for(auto ligne : grille) {
		for(auto kase : ligne) {
			if( kase == VIDE) {
				cout << "|___";
			} else if ( kase == CARRE) {
				cout << "|_X_";
			}
		}
		cout << endl;
	}
}

	
