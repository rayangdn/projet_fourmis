#include <iostream>
#include <array>
#include <vector>

#include "Code_source/constantes.h"
#include  "Code_source/error_squarecell.h"
//#include "carre.h"

using namespace std;
enum {VIDE, CARRE, POINT};
typedef array<array<unsigned int, 10> ,10> Grille;
typedef vector<vector<unsigned int>> Carre;
struct Point {
	unsigned int x;
	unsigned int y;
};
void initalise(Grille& grille);
void initialise1(Point point, Grille& grille);
void affiche(Grille grille);

void test_validation_carre(Carre carre, Grille grille, Point point); 
int main() {
	Grille grille;
	Carre carre(5, vector<unsigned int> (5));
	Point point{2,3};
	initalise(grille);
	initialise1(point, grille);
	affiche(grille);
	test_validation_carre(carre, grille, point);

	

	return 0;
}
void initalise(Grille& grille) {
	for(auto& ligne : grille) {
		for(auto& kase : ligne) {
			kase = VIDE;
			
		}
	}
}
void initialise1(Point point, Grille& grille) {
	for(size_t i(0); i < grille.size(); ++i) {
		for(size_t j(0); j < grille[i].size(); ++j) {
			if( j+1 == point.x and i == 10-point.y) {
				grille[i][j] = POINT;
			}
			
		}
	}
}
void affiche(Grille grille) {
	for(auto ligne : grille) {
		for(auto kase : ligne) {
			if( kase == VIDE) {
				cout << "|___";
			} else if ( kase == POINT) {
				cout << "|_X_";
			}
		}
		cout << endl;
	}
}
void test_validation_carre(Carre carre, Grille grille, Point point) {
}
	
