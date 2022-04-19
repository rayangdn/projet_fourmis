//projet.cc
//Rayan Gauderon membre 1: 100%
//Maxime Luyet membre 2: 0%

#include <iostream>
#include <vector>
#include <gtkmm.h>
#include <utility>


#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char* argv[]) {
	initialise_grid(g_max);

	/*if(argc != 2){
		exit(0);
	}
	simulation.lecture(argv[1]);
	*/
	Simulation simulation;
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
		MyEvent myevent(std::move(simulation));
		
		
		return app->run(myevent);
}
