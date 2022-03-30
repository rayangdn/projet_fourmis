#include <iostream>
#include <vector>

#include "simulation.h"


using namespace std;



int main(int argc, char * argv[]) {
	static Grid grid;
	const unsigned int g_max(pow(2,g_dim));
	initialise_grid(grid, g_max);
	Simulation simulation(grid);
	if(argc != 2){
		exit(0);
	 }
	
	simulation.lecture(argv[1]); 
	 return EXIT_SUCCESS;

	
	
	return 0;
	
	
}
	//const unsigned int g_max = pow(2, g_dim);
	

