#include <iostream>
#include <array>
#include <vector>
using namespace std;
enum Rempli{CARRE,VIDE};
typedef array<array<unsigned int , 10>, 10> Grille;
typedef array<array<unsigned int, 4>, 4> Carre;
void initialise(Grille& grille) {
	for(auto &ligne : grille) {
		for(auto &kase : ligne) {
			kase = VIDE ;
			
		}
		
	}
}

void affiche(Grille& grille, unsigned int x, unsigned int y,const Carre& carre) {
	for(size_t i(0); i < grille.size() ; ++i) {
		for(size_t j(0); j < grille[i].size() ; ++j) {
			if( i == grille.size()-1-x and j == y) {
			grille[i][j] = CARRE;
			cout << "| X";
			
			} else {
				cout << "|__";
			}
		}
		cout <<endl;
	}
			
}

int main() {
	unsigned int x(0);
	unsigned int y(0);
	Grille grille;
	Carre carre;
	initialise(grille);
	
	affiche(grille, x, y, carre);
	
	
	
	return 0;
}
