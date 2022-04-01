#include <iostream>
#include <vector>

#include "simulation.h"

using namespace std;

int main(int argc, char * argv[]) {
	initialise_grid(g_max);
	Simulation simulation;
	if(argc != 2){
		exit(0);
	 }
	simulation.lecture(argv[1]); 
	return EXIT_SUCCESS;
}
