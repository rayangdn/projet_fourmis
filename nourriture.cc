#include <iostream>
#include <vector>
#include <array>
#include "Code_source/constantes.h"
using namespace std;
enum {VIDE, CARRE};
typedef array<array<unsigned int, 20> ,20> Grille;
struct Point {
	unsigned int x;
	unsigned int y;
};
class Nourriture {
	void creer_nourriture();
	private :
	vector<Point> points; // du module squarecell
	

};
void initialise(Grille& grid) {
	for(auto& ligne : grid) {
		for(auto& kase : ligne) {
			kase = VIDE;
		}
	}
}
void affiche(Grille grid) {
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if( kase == VIDE) {
				cout << "|___";
			} else if ( kase ==CARRE) {
				cout << "|_X_";
			}
		}
		cout << endl;
	}
}
int main() {
	Grille grid;
	initialise(grid);
	affiche(grid);

	return 0;
}
void Nourriture::creer_nourriture() {
	
}
