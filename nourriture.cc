#include <iostream>
#include <vector>
#include <array>
#include "Code_source/constantes.h"
using namespace std;

typedef array<array<bool, 10> ,10> Grille;
struct Point {
	unsigned int x;
	unsigned int y;
};
void initialise_carre(Grille& grid, Point point);
class Nourriture {
	public :
	Nourriture(unsigned int x, unsigned int y, unsigned int val_food)
	:  point{x,y}, val_food(val_food) {}
	void creer_nourriture();
	
	private :
	Point point;
	unsigned int val_food;// du module constante
	
	

};
void initialise(Grille& grid) {
	for(auto& ligne : grid) {
		for(auto& kase : ligne) {
			kase = false;
		}
	}
}
void affiche(Grille grid) {
	for(auto ligne : grid) {
		for(auto kase : ligne) {
			if( kase == false) {
				cout << "|___";
			} else if ( kase ==true) {
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
	Nourriture nourriture( 4, 5, 50);
	
	return 0;
}
void Nourriture::creer_nourriture() {
	double p;
	//bernoulli_distribution b(p);
	//default_random_engine e;
	//if(b(e)) {
	//}
}
void initialise_carre(Grille& grid, Point point){
	for(size_t i(0); i < grid.size(); ++i) {
		for(size_t j(0); j < grid[i].size(); ++j) {
			if( j == point.x and i == grid.size()-point.y) {
				grid[grid.size()-point.y][point.x] = true;
			}
		}
	}
}
