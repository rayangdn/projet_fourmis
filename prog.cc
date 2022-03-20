#include <iostream>
#include <vector>
#include "squarecell.h"
#include "simulation.h"

using namespace std;


int main(int argc, char * argv[]) {
	
	if(argc != 2){
		 exit(0);
	 }
	
	lecture(argv[1]); 
	 return EXIT_SUCCESS;

	/*static Grid grid;
	const unsigned int g_max(10);
	Carre carre0{2, {4, 4}};
	Carre carre1{1, {1, 1}};
	Carre carre2{1, { 3,7}};
	Carre carre3{1, {8, 1}};
	Ensemble_carre ensemble_carre;
	ensemble_carre.push_back(carre0);
	ensemble_carre.push_back(carre1);
	ensemble_carre.push_back(carre2);
	initialise_grid(grid, g_max);
	test_validation_carre(grid,carre0);
	test_validation_carre(grid,carre1);
	test_validation_carre(grid,carre2);
	test_validation_carre(grid,carre3);
	initialise_carre(grid, carre0);
	initialise_carre(grid, carre1);
	initialise_carre(grid, carre2);
	//initialise_carre(grid, carre3);
	// le carre 3 initialiser ou doit etre initialiser après le test de superposition??
	if( test_superposition(grid, carre3, ensemble_carre)) {
		initialise_carre(grid, carre3);
	}
	affiche_grid(grid);
	
	return 0;
	*/
	
}
	//const unsigned int g_max = pow(2, g_dim);
	

